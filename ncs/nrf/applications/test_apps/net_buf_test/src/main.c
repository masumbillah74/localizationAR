/*
 * Copyright (c) 2012-2014 Wind River Systems, Inc.
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include <zephyr.h>
#include <sys/printk.h>
#include <net/buf.h>

struct local_head {
	u8_t idx;
	u8_t value;
};

struct local_data {
	u8_t idx;
	u8_t value;
};

struct local_tail {
	u8_t idx;
	u8_t value;
};

struct pdu {
	struct local_data data1;
	struct local_data data2;
	struct local_data data3;
};

#define NUMBER_OF_BUFFERS 10u

void destroy_buf(struct net_buf *buf)
{
	printk("Buffer %p is going to be destroyed\n", buf);

	net_buf_destroy(buf);
}

#define PDU_SIZE (sizeof(struct local_head) + sizeof(struct local_data) + sizeof(struct local_tail))

NET_BUF_POOL_FIXED_DEFINE(local_net_buf, NUMBER_OF_BUFFERS, PDU_SIZE, destroy_buf);
NET_BUF_POOL_FIXED_DEFINE(local_net_buf_frag, NUMBER_OF_BUFFERS, sizeof(struct local_data), destroy_buf);

struct net_buf *create_buf()
{
	struct net_buf * buf;

	buf = net_buf_alloc(&local_net_buf, K_NO_WAIT);
	if (buf == NULL) {
		printk("Error while net buff allocation!\n");
	}

	printk("Buf headroom %d\n", net_buf_headroom(buf));
	printk("Buf tailroom %d\n", net_buf_tailroom(buf));

	net_buf_reserve(buf, sizeof(struct local_head));

	printk("Buf headroom %d\n", net_buf_headroom(buf));
	printk("Buf tailroom %d\n", net_buf_tailroom(buf));

	struct local_head* head;
	struct local_data* data;
	struct local_tail* tail;

	data = net_buf_add(buf,sizeof(*data));
	if (data == NULL) {
		printk("Can't add data to buffer\n");
	}

	data->idx = 1;
	data->value=11;

	printk("Buf headroom %d\n", net_buf_headroom(buf));
	printk("Buf tailroom %d\n", net_buf_tailroom(buf));

	head = net_buf_push(buf, sizeof(struct local_head));
	if (head == NULL) {
		printk("Can't add head to buffer\n");
	}

	head->idx = 2;
	head->value=22;

	printk("Buf headroom %d\n", net_buf_headroom(buf));
	printk("Buf tailroom %d\n", net_buf_tailroom(buf));

	tail = net_buf_add(buf, sizeof(struct local_tail));
	if (tail == NULL) {
		printk("Can't add head to buffer\n");
	}

	tail->idx = 3;
	tail->value=33;

	printk("Buf headroom %d\n", net_buf_headroom(buf));
	printk("Buf tailroom %d\n", net_buf_tailroom(buf));

	return buf;
}

void print_buf(struct net_buf *buf)
{
	printk("Buf headroom %d\n", net_buf_headroom(buf));
	printk("Buf tailroom %d\n", net_buf_tailroom(buf));

	struct local_head* head;
	struct local_data* data;
	struct local_tail* tail;

	head = net_buf_pull(buf, sizeof(struct local_head));
	if (head == NULL) {
		printk("Can't poll head from buffer\n");
	}

	printk("Buf head->id %d\n", head->idx);
	printk("Buf head->value %d\n", head->value);

	printk("Buf headroom %d\n", net_buf_headroom(buf));
	printk("Buf tailroom %d\n", net_buf_tailroom(buf));

	data = net_buf_pull(buf, sizeof(struct local_data));
	if (data == NULL) {
		printk("Can't poll datafrom buffer\n");
	}

	printk("Buf data->id %d\n", data->idx);
	printk("Buf data->value %d\n", data->value);

	printk("Buf headroom %d\n", net_buf_headroom(buf));
	printk("Buf tailroom %d\n", net_buf_tailroom(buf));

	tail = net_buf_pull(buf, sizeof(struct local_tail));
	if (tail == NULL) {
		printk("Can't poll tail from buffer\n");
	}

	printk("Buf tail->id %d\n", tail->idx);
	printk("Buf tail->value %d\n", tail->value);

	printk("Buf headroom %d\n", net_buf_headroom(buf));
	printk("Buf tailroom %d\n", net_buf_tailroom(buf));

	data = net_buf_add(buf,sizeof(*data));
	if (data == NULL) {
		printk("Can't add data to buffer\n");
	}

	data->idx = 1;
	data->value=11;

	printk("Buf headroom %d\n", net_buf_headroom(buf));
	printk("Buf tailroom %d\n", net_buf_tailroom(buf));
}

struct net_buf* prepare_freg(u8_t idx, u8_t value)
{
	struct local_data* data;
	struct net_buf *buf;

	buf = net_buf_alloc(&local_net_buf, K_NO_WAIT);
	if (buf == NULL) {
		printk("Error while net buff allocation!\n");
	}

	data = net_buf_add(buf,sizeof(*data));
	if (data == NULL) {
		printk("Can't add data to buffer\n");
	}

	data->idx = idx;
	data->value=value;

	return buf;
}

struct net_buf* add_to_chain(struct net_buf* head, struct net_buf* frag)
{
	head = net_buf_frag_add(head, frag);
	printk("Chain total len: %d\n", net_buf_frags_len(head));

	return head;
}

struct pdu concatenate_chain(struct net_buf* chain)
{
	struct pdu data;

	net_buf_linearize(&data, sizeof(data), chain, 0, sizeof(data));
	return data;
}

struct net_buf *create_buf_chain()
{
	struct net_buf *chain = NULL;
	struct net_buf *buf;

	buf = prepare_freg(1,11);
	chain = add_to_chain(chain, buf);

	buf = prepare_freg(2,22);
	chain = add_to_chain(chain, buf);

	buf = prepare_freg(3,33);
	chain = add_to_chain(chain, buf);

	return chain;
}

void main(void)
{
//	struct net_buf * buf;

//	buf = create_buf();
//	print_buf(buf);

	struct net_buf *chain;
	chain = create_buf_chain();

	struct pdu data;
	data = concatenate_chain(chain);

	struct local_data *data1;
	struct net_buf *offset_buf;

	printk("Chain total len: %d\n", net_buf_frags_len(chain));
	//offset_buf = net_buf_skip(chain, 2*sizeof(struct local_data));
	size_t len =  2*sizeof(struct local_data);
	while (chain && len--) {
		net_buf_pull_u8(chain);
		if (!chain->len) {
			chain = net_buf_frag_del(NULL, chain);
		}
	}

	data1 = (struct local_data*)offset_buf->data;

	printk("idx: %d, value: %d\n", data1->idx, data1->value);
	printk("Chain total len: %d\n", net_buf_frags_len(offset_buf));
	printk("Hello World! %s\n", CONFIG_BOARD);
}
