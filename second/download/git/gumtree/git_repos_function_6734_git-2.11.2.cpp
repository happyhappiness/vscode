static inline void NORETURN pthread_exit(void *ret)
{
	ExitThread((DWORD)(intptr_t)ret);
}