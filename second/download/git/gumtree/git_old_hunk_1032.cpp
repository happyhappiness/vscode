
		if (item[i].nowildcard_len < item[i].len)
			pathspec->has_wildcard = 1;
		pathspec->magic |= item[i].magic;
	}

	if (nr_exclude == n)
		die(_("There is nothing to exclude from by :(exclude) patterns.\n"
		      "Perhaps you forgot to add either ':/' or '.' ?"));


	if (pathspec->magic & PATHSPEC_MAXDEPTH) {
		if (flags & PATHSPEC_KEEP_ORDER)
			die("BUG: PATHSPEC_MAXDEPTH_VALID and PATHSPEC_KEEP_ORDER are incompatible");
		QSORT(pathspec->items, pathspec->nr, pathspec_item_cmp);
	}
}

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

void clear_pathspec(struct pathspec *pathspec)
{
	int i;

	for (i = 0; i < pathspec->nr; i++) {
		free(pathspec->items[i].match);
		free(pathspec->items[i].original);
	}
	free(pathspec->items);
	pathspec->items = NULL;
	pathspec->nr = 0;
}
