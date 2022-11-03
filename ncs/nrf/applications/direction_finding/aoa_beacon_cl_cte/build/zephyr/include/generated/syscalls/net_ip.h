
/* auto-generated by gen_syscalls.py, don't edit */
#ifndef Z_INCLUDE_SYSCALLS_NET_IP_H
#define Z_INCLUDE_SYSCALLS_NET_IP_H


#ifndef _ASMLANGUAGE

#include <syscall_list.h>
#include <syscall.h>

#if __GNUC__ > 4 || (__GNUC__ == 4 && __GNUC_MINOR__ >= 6)
#pragma GCC diagnostic push
#endif

#ifdef __GNUC__
#pragma GCC diagnostic ignored "-Wstrict-aliasing"
#endif

#ifdef __cplusplus
extern "C" {
#endif

extern int z_impl_net_addr_pton(sa_family_t family, const char * src, void * dst);
static inline int net_addr_pton(sa_family_t family, const char * src, void * dst)
{
#ifdef CONFIG_USERSPACE
	if (z_syscall_trap()) {
		return (int) arch_syscall_invoke3(*(uintptr_t *)&family, *(uintptr_t *)&src, *(uintptr_t *)&dst, K_SYSCALL_NET_ADDR_PTON);
	}
#endif
	compiler_barrier();
	return z_impl_net_addr_pton(family, src, dst);
}


extern char * z_impl_net_addr_ntop(sa_family_t family, const void * src, char * dst, size_t size);
static inline char * net_addr_ntop(sa_family_t family, const void * src, char * dst, size_t size)
{
#ifdef CONFIG_USERSPACE
	if (z_syscall_trap()) {
		return (char *) arch_syscall_invoke4(*(uintptr_t *)&family, *(uintptr_t *)&src, *(uintptr_t *)&dst, *(uintptr_t *)&size, K_SYSCALL_NET_ADDR_NTOP);
	}
#endif
	compiler_barrier();
	return z_impl_net_addr_ntop(family, src, dst, size);
}


#ifdef __cplusplus
}
#endif

#if __GNUC__ > 4 || (__GNUC__ == 4 && __GNUC_MINOR__ >= 6)
#pragma GCC diagnostic pop
#endif

#endif
#endif /* include guard */
