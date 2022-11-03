#!/usr/bin/env python3
#
#  Copyright (c) 2016, The OpenThread Authors.
#  All rights reserved.
#
#  Redistribution and use in source and binary forms, with or without
#  modification, are permitted provided that the following conditions are met:
#  1. Redistributions of source code must retain the above copyright
#     notice, this list of conditions and the following disclaimer.
#  2. Redistributions in binary form must reproduce the above copyright
#     notice, this list of conditions and the following disclaimer in the
#     documentation and/or other materials provided with the distribution.
#  3. Neither the name of the copyright holder nor the
#     names of its contributors may be used to endorse or promote products
#     derived from this software without specific prior written permission.
#
#  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
#  AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
#  IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
#  ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE
#  LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
#  CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
#  SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
#  INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
#  CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
#  ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
#  POSSIBILITY OF SUCH DAMAGE.
#

import unittest

import thread_cert

COMMISSIONER = 1
JOINER_ROUTER = 2
JOINER = 3


class Cert_8_2_02_JoinerRouter(thread_cert.TestCase):
    topology = {
        COMMISSIONER: {
            'masterkey': 'deadbeefdeadbeefdeadbeefdeadbeef',
            'mode': 'rsdn',
            'panid': 0xface,
            'router_selection_jitter': 1
        },
        JOINER_ROUTER: {
            'masterkey': '00112233445566778899aabbccddeeff',
            'mode': 'rsdn',
            'router_selection_jitter': 1
        },
        JOINER: {
            'masterkey': '00112233445566778899aabbccddeeff',
            'mode': 'rsdn',
            'router_selection_jitter': 1
        },
    }

    def test(self):
        self.nodes[COMMISSIONER].interface_up()
        self.nodes[COMMISSIONER].thread_start()
        self.simulator.go(5)
        self.assertEqual(self.nodes[COMMISSIONER].get_state(), 'leader')

        self.nodes[COMMISSIONER].commissioner_start()
        self.simulator.go(5)
        self.nodes[COMMISSIONER].commissioner_add_joiner(
            self.nodes[JOINER_ROUTER].get_eui64(), 'OPENTHREAD')
        self.nodes[COMMISSIONER].commissioner_add_joiner(
            self.nodes[JOINER].get_eui64(), 'OPENTHREAD2')
        self.simulator.go(5)

        self.nodes[COMMISSIONER].add_whitelist(
            self.nodes[JOINER_ROUTER].get_joiner_id())
        self.nodes[JOINER_ROUTER].add_whitelist(
            self.nodes[COMMISSIONER].get_addr64())

        self.nodes[JOINER_ROUTER].interface_up()
        self.nodes[JOINER_ROUTER].joiner_start('OPENTHREAD')
        self.simulator.go(10)
        self.assertEqual(
            self.nodes[JOINER_ROUTER].get_masterkey(),
            self.nodes[COMMISSIONER].get_masterkey(),
        )

        self.nodes[COMMISSIONER].add_whitelist(
            self.nodes[JOINER_ROUTER].get_addr64())

        self.nodes[JOINER_ROUTER].thread_start()
        self.simulator.go(5)
        self.assertEqual(self.nodes[JOINER_ROUTER].get_state(), 'router')

        self.nodes[JOINER_ROUTER].add_whitelist(
            self.nodes[JOINER].get_joiner_id())
        self.nodes[JOINER].add_whitelist(self.nodes[JOINER_ROUTER].get_addr64())

        self.nodes[JOINER].interface_up()
        self.nodes[JOINER].joiner_start('2DAERHTNEPO')
        self.simulator.go(10)
        self.assertNotEqual(
            self.nodes[JOINER].get_masterkey(),
            self.nodes[COMMISSIONER].get_masterkey(),
        )


if __name__ == '__main__':
    unittest.main()