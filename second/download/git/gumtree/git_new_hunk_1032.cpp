
		if (item[i].nowildcard_len < item[i].len)
			pathspec->has_wildcard = 1;
		pathspec->magic |= item[i].magic;
	}

	/*
	 * If everything is an exclude pattern, add one positive pattern
	 * that matches everyting. We allocated an extra one for this.
	 */
	if (nr_exclude == n) {
		int plen = (!(flags & PATHSPEC_PREFER_CWD)) ? 0 : prefixlen;
		init_pathspec_item(item + n, 0, prefix, plen, "");
		pathspec->nr++;
	}

	if (pathspec->magic & PATHSPEC_MAXDEPTH) {
		if (flags & PATHSPEC_KEEP_ORDER)
			die("BUG: PATHSPEC_MAXDEPTH_VALID and PATHSPEC_KEEP_ORDER are incompatible");
		QSORT(pathspec->items, pathspec->nr, pathspec_item_cmp);
	}
}

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

void clear_pathspec(struct pathspec *pathspec)
{
	int i, j;

	for (i = 0; i < pathspec->nr; i++) {
		free(pathspec->items[i].match);
		free(pathspec->items[i].original);

		for (j = 0; j < pathspec->items[i].attr_match_nr; j++)
			free(pathspec->items[i].attr_match[j].value);
		free(pathspec->items[i].attr_match);

		if (pathspec->items[i].attr_check)
			attr_check_free(pathspec->items[i].attr_check);
	}

	free(pathspec->items);
	pathspec->items = NULL;
	pathspec->nr = 0;
}
