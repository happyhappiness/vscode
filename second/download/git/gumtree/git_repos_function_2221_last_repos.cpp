static void *get_next_packed_git(const void *p)
{
	return ((const struct packed_git *)p)->next;
}