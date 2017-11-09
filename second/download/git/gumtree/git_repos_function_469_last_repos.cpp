static void set_next_blame(void *p1, void *p2)
{
	((struct blame_entry *)p1)->next = p2;
}