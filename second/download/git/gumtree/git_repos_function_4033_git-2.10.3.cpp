void copy_pathspec(struct pathspec *dst, const struct pathspec *src)
{
	*dst = *src;
	ALLOC_ARRAY(dst->items, dst->nr);
	COPY_ARRAY(dst->items, src->items, dst->nr);
}