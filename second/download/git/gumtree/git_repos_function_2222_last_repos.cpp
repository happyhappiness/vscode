static void set_next_packed_git(void *p, void *next)
{
	((struct packed_git *)p)->next = next;
}