static void NORETURN async_exit(int code)
{
	pthread_exit((void *)(intptr_t)code);
}