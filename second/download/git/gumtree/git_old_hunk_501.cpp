		      "Perhaps you forgot to add either ':/' or '.' ?"));


	if (pathspec->magic & PATHSPEC_MAXDEPTH) {
		if (flags & PATHSPEC_KEEP_ORDER)
			die("BUG: PATHSPEC_MAXDEPTH_VALID and PATHSPEC_KEEP_ORDER are incompatible");
		qsort(pathspec->items, pathspec->nr,
		      sizeof(struct pathspec_item), pathspec_item_cmp);
	}
}

/*
 * N.B. get_pathspec() is deprecated in favor of the "struct pathspec"
 * based interface - see pathspec.c:parse_pathspec().
