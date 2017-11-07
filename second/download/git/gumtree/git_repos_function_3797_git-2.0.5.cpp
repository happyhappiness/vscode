static void dup_entry(struct blame_entry *dst, struct blame_entry *src)
{
	struct blame_entry *n;

	n = dst->next;
	origin_incref(src->suspect);
	origin_decref(dst->suspect);
	memcpy(dst, src, sizeof(*src));
	dst->next = n;
	dst->score = 0;
}