static void *get_next_blame(const void *p)
{
	return ((struct blame_entry *)p)->next;
}