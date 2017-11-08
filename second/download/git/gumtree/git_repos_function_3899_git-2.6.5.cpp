void copy_pathspec(struct pathspec *dst, const struct pathspec *src)
{
	*dst = *src;
	dst->items = xmalloc(sizeof(struct pathspec_item) * dst->nr);
	memcpy(dst->items, src->items,
	       sizeof(struct pathspec_item) * dst->nr);
}