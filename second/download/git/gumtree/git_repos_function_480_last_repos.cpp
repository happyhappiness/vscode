static void add_blame_entry(struct blame_entry ***queue,
			    const struct blame_entry *src)
{
	struct blame_entry *e = xmalloc(sizeof(*e));
	memcpy(e, src, sizeof(*e));
	blame_origin_incref(e->suspect);

	e->next = **queue;
	**queue = e;
	*queue = &e->next;
}