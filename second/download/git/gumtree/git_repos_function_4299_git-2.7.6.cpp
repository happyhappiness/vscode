static void add_blame_entry(struct blame_entry ***queue, struct blame_entry *e)
{
	origin_incref(e->suspect);

	e->next = **queue;
	**queue = e;
	*queue = &e->next;
}