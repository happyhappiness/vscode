static void dup_entry(struct blame_entry ***queue,
		      struct blame_entry *dst, struct blame_entry *src)
{
	blame_origin_incref(src->suspect);
	blame_origin_decref(dst->suspect);
	memcpy(dst, src, sizeof(*src));
	dst->next = **queue;
	**queue = dst;
	*queue = &dst->next;
}