unsigned int alloc_commit_index(void)
{
	static unsigned int count;
	return count++;
}