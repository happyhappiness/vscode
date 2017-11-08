void copy_pathspec(struct pathspec *dst, const struct pathspec *src)
{
	int i, j;

	*dst = *src;
	ALLOC_ARRAY(dst->items, dst->nr);
	COPY_ARRAY(dst->items, src->items, dst->nr);

	for (i = 0; i < dst->nr; i++) {
		struct pathspec_item *d = &dst->items[i];
		struct pathspec_item *s = &src->items[i];

		d->match = xstrdup(s->match);
		d->original = xstrdup(s->original);

		ALLOC_ARRAY(d->attr_match, d->attr_match_nr);
		COPY_ARRAY(d->attr_match, s->attr_match, d->attr_match_nr);
		for (j = 0; j < d->attr_match_nr; j++) {
			const char *value = s->attr_match[j].value;
			d->attr_match[j].value = xstrdup_or_null(value);
		}

		d->attr_check = attr_check_dup(s->attr_check);
	}
}