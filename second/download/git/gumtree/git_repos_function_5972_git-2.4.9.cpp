static inline int pthread_exit(void *ret)
{
	ExitThread((DWORD)ret);
}