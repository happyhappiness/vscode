int git_munmap(void *start, size_t length)
{
	return !UnmapViewOfFile(start);
}