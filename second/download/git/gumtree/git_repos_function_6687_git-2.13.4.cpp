int git_munmap(void *start, size_t length)
{
	free(start);
	return 0;
}