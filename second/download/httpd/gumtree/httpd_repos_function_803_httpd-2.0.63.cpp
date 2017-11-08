static void shmcb_safe_clear(void *ptr, size_t size)
{
	memset(ptr, 0, size);
}