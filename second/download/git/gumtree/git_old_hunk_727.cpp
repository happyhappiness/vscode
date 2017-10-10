		    item->match[item->nowildcard_len] == '*' &&
		    no_wildcard(item->match + item->nowildcard_len + 1))
			item->flags |= PATHSPEC_ONESTAR;
	}

	/* sanity checks, pathspec matchers assume these are sane */
	assert(item->nowildcard_len <= item->len &&
	       item->prefix         <= item->len);
	return magic;
}

static int pathspec_item_cmp(const void *a_, const void *b_)
{
	struct pathspec_item *a, *b;

	a = (struct pathspec_item *)a_;
	b = (struct pathspec_item *)b_;
	return strcmp(a->match, b->match);
}

static void NORETURN unsupported_magic(const char *pattern,
				       unsigned magic,
				       unsigned short_magic)
{
	struct strbuf sb = STRBUF_INIT;
	int i, n;
	for (n = i = 0; i < ARRAY_SIZE(pathspec_magic); i++) {
		const struct pathspec_magic *m = pathspec_magic + i;
		if (!(magic & m->bit))
			continue;
		if (sb.len)
			strbuf_addch(&sb, ' ');
		if (short_magic & m->bit)
			strbuf_addf(&sb, "'%c'", m->mnemonic);
		else
			strbuf_addf(&sb, "'%s'", m->name);
		n++;
	}
	/*
	 * We may want to substitute "this command" with a command
	 * name. E.g. when add--interactive dies when running
	 * "checkout -p"
	 */
