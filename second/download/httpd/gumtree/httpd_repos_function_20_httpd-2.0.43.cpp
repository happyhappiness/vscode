static void *get_shared_mem(apr_size_t size)
{
    void *result;

    /* allocate shared memory for the shared_counter */
    result = (unsigned long *)mmap ((caddr_t)0, size,
		    PROT_READ|PROT_WRITE, MAP_ANON|MAP_SHARED, -1, 0);
    if (result == (void *)(caddr_t)-1) {
	perror ("mmap");
	exit (1);
    }
    return result;
}