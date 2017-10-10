			item->flags |= PATHSPEC_ONESTAR;
	}

	/* sanity checks, pathspec matchers assume these are sane */
	if (item->nowildcard_len > item->len ||
	    item->prefix         > item->len) {
		die ("BUG: error initializing pathspec_item");
	}
}

static int pathspec_item_cmp(const void *a_, const void *b_)
{
	struct pathspec_item *a, *b;
