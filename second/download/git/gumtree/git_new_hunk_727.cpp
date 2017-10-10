		    item->match[item->nowildcard_len] == '*' &&
		    no_wildcard(item->match + item->nowildcard_len + 1))
			item->flags |= PATHSPEC_ONESTAR;
	}

	/* sanity checks, pathspec matchers assume these are sane */
	if (item->nowildcard_len > item->len ||
	    item->prefix         > item->len) {
		/*
		 * This case can be triggered by the user pointing us to a
		 * pathspec inside a submodule, which is an input error.
		 * Detect that here and complain, but fallback in the
		 * non-submodule case to a BUG, as we have no idea what
		 * would trigger that.
		 */
		die_inside_submodule_path(item);
		die ("BUG: item->nowildcard_len > item->len || item->prefix > item->len)");
	}
}

static int pathspec_item_cmp(const void *a_, const void *b_)
{
	struct pathspec_item *a, *b;

	a = (struct pathspec_item *)a_;
	b = (struct pathspec_item *)b_;
	return strcmp(a->match, b->match);
}

static void NORETURN unsupported_magic(const char *pattern,
				       unsigned magic)
{
	struct strbuf sb = STRBUF_INIT;
	int i;
	for (i = 0; i < ARRAY_SIZE(pathspec_magic); i++) {
		const struct pathspec_magic *m = pathspec_magic + i;
		if (!(magic & m->bit))
			continue;
		if (sb.len)
			strbuf_addstr(&sb, ", ");

		if (m->mnemonic)
			strbuf_addf(&sb, _("'%s' (mnemonic: '%c')"),
				    m->name, m->mnemonic);
		else
			strbuf_addf(&sb, "'%s'", m->name);
	}
	/*
	 * We may want to substitute "this command" with a command
	 * name. E.g. when add--interactive dies when running
	 * "checkout -p"
	 */
