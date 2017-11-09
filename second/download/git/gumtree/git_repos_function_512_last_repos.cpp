struct blame_entry *blame_entry_prepend(struct blame_entry *head,
					long start, long end,
					struct blame_origin *o)
{
	struct blame_entry *new_head = xcalloc(1, sizeof(struct blame_entry));
	new_head->lno = start;
	new_head->num_lines = end - start;
	new_head->suspect = o;
	new_head->s_lno = start;
	new_head->next = head;
	blame_origin_incref(o);
	return new_head;
}