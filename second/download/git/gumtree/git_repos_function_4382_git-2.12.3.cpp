void copy_pathspec(struct pathspec *dst, const struct pathspec *src)
{
	int i;

	*dst = *src;
	ALLOC_ARRAY(dst->items, dst->nr);
	COPY_ARRAY(dst->items, src->items, dst->nr);

	for (i = 0; i < dst->nr; i++) {
		dst->items[i].match = xstrdup(src->items[i].match);
		dst->items[i].original = xstrdup(src->items[i].original);
	}
}