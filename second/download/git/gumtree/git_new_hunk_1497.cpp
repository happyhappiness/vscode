		return parse_long_magic(magic, prefix_len, item, elem);
	else
		/* shorthand */
		return parse_short_magic(magic, elem);
}

/*
 * Perform the initialization of a pathspec_item based on a pathspec element.
 */
static void init_pathspec_item(struct pathspec_item *item, unsigned flags,
			       const char *prefix, int prefixlen,
			       const char *elt)
