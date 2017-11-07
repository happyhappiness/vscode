void copy_pathspec(struct pathspec *dst, const struct pathspec *src)
{
	*dst = *src;
	ALLOC_ARRAY(dst->items, dst->nr);
	memcpy(dst->items, src->items,
	       sizeof(struct pathspec_item) * dst->nr);
}