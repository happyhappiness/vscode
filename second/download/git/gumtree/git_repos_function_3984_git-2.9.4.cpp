static unsigned prefix_pathspec(struct pathspec_item *item,
				unsigned *p_short_magic,
				const char **raw, unsigned flags,
				const char *prefix, int prefixlen,
				const char *elt)
{
	static int literal_global = -1;
	static int glob_global = -1;
	static int noglob_global = -1;
	static int icase_global = -1;
	unsigned magic = 0, short_magic = 0, global_magic = 0;
	const char *copyfrom = elt, *long_magic_end = NULL;
	char *match;
	int i, pathspec_prefix = -1;

	if (literal_global < 0)
		literal_global = git_env_bool(GIT_LITERAL_PATHSPECS_ENVIRONMENT, 0);
	if (literal_global)
		global_magic |= PATHSPEC_LITERAL;

	if (glob_global < 0)
		glob_global = git_env_bool(GIT_GLOB_PATHSPECS_ENVIRONMENT, 0);
	if (glob_global)
		global_magic |= PATHSPEC_GLOB;

	if (noglob_global < 0)
		noglob_global = git_env_bool(GIT_NOGLOB_PATHSPECS_ENVIRONMENT, 0);

	if (glob_global && noglob_global)
		die(_("global 'glob' and 'noglob' pathspec settings are incompatible"));


	if (icase_global < 0)
		icase_global = git_env_bool(GIT_ICASE_PATHSPECS_ENVIRONMENT, 0);
	if (icase_global)
		global_magic |= PATHSPEC_ICASE;

	if ((global_magic & PATHSPEC_LITERAL) &&
	    (global_magic & ~PATHSPEC_LITERAL))
		die(_("global 'literal' pathspec setting is incompatible "
		      "with all other global pathspec settings"));

	if (flags & PATHSPEC_LITERAL_PATH)
		global_magic = 0;

	if (elt[0] != ':' || literal_global ||
	    (flags & PATHSPEC_LITERAL_PATH)) {
		; /* nothing to do */
	} else if (elt[1] == '(') {
		/* longhand */
		const char *nextat;
		for (copyfrom = elt + 2;
		     *copyfrom && *copyfrom != ')';
		     copyfrom = nextat) {
			size_t len = strcspn(copyfrom, ",)");
			if (copyfrom[len] == ',')
				nextat = copyfrom + len + 1;
			else
				/* handle ')' and '\0' */
				nextat = copyfrom + len;
			if (!len)
				continue;
			for (i = 0; i < ARRAY_SIZE(pathspec_magic); i++) {
				if (strlen(pathspec_magic[i].name) == len &&
				    !strncmp(pathspec_magic[i].name, copyfrom, len)) {
					magic |= pathspec_magic[i].bit;
					break;
				}
				if (starts_with(copyfrom, "prefix:")) {
					char *endptr;
					pathspec_prefix = strtol(copyfrom + 7,
								 &endptr, 10);
					if (endptr - copyfrom != len)
						die(_("invalid parameter for pathspec magic 'prefix'"));
					/* "i" would be wrong, but it does not matter */
					break;
				}
			}
			if (ARRAY_SIZE(pathspec_magic) <= i)
				die(_("Invalid pathspec magic '%.*s' in '%s'"),
				    (int) len, copyfrom, elt);
		}
		if (*copyfrom != ')')
			die(_("Missing ')' at the end of pathspec magic in '%s'"), elt);
		long_magic_end = copyfrom;
		copyfrom++;
	} else {
		/* shorthand */
		for (copyfrom = elt + 1;
		     *copyfrom && *copyfrom != ':';
		     copyfrom++) {
			char ch = *copyfrom;

			if (!is_pathspec_magic(ch))
				break;
			for (i = 0; i < ARRAY_SIZE(pathspec_magic); i++)
				if (pathspec_magic[i].mnemonic == ch) {
					short_magic |= pathspec_magic[i].bit;
					break;
				}
			if (ARRAY_SIZE(pathspec_magic) <= i)
				die(_("Unimplemented pathspec magic '%c' in '%s'"),
				    ch, elt);
		}
		if (*copyfrom == ':')
			copyfrom++;
	}

	magic |= short_magic;
	*p_short_magic = short_magic;

	/* --noglob-pathspec adds :(literal) _unless_ :(glob) is specified */
	if (noglob_global && !(magic & PATHSPEC_GLOB))
		global_magic |= PATHSPEC_LITERAL;

	/* --glob-pathspec is overridden by :(literal) */
	if ((global_magic & PATHSPEC_GLOB) && (magic & PATHSPEC_LITERAL))
		global_magic &= ~PATHSPEC_GLOB;

	magic |= global_magic;

	if (pathspec_prefix >= 0 &&
	    (prefixlen || (prefix && *prefix)))
		die("BUG: 'prefix' magic is supposed to be used at worktree's root");

	if ((magic & PATHSPEC_LITERAL) && (magic & PATHSPEC_GLOB))
		die(_("%s: 'literal' and 'glob' are incompatible"), elt);

	if (pathspec_prefix >= 0) {
		match = xstrdup(copyfrom);
		prefixlen = pathspec_prefix;
	} else if (magic & PATHSPEC_FROMTOP) {
		match = xstrdup(copyfrom);
		prefixlen = 0;
	} else {
		match = prefix_path_gently(prefix, prefixlen, &prefixlen, copyfrom);
		if (!match)
			die(_("%s: '%s' is outside repository"), elt, copyfrom);
	}
	*raw = item->match = match;
	/*
	 * Prefix the pathspec (keep all magic) and assign to
	 * original. Useful for passing to another command.
	 */
	if (flags & PATHSPEC_PREFIX_ORIGIN) {
		struct strbuf sb = STRBUF_INIT;
		if (prefixlen && !literal_global) {
			/* Preserve the actual prefix length of each pattern */
			if (short_magic)
				prefix_short_magic(&sb, prefixlen, short_magic);
			else if (long_magic_end) {
				strbuf_add(&sb, elt, long_magic_end - elt);
				strbuf_addf(&sb, ",prefix:%d)", prefixlen);
			} else
				strbuf_addf(&sb, ":(prefix:%d)", prefixlen);
		}
		strbuf_addstr(&sb, match);
		item->original = strbuf_detach(&sb, NULL);
	} else
		item->original = elt;
	item->len = strlen(item->match);
	item->prefix = prefixlen;

	if ((flags & PATHSPEC_STRIP_SUBMODULE_SLASH_CHEAP) &&
	    (item->len >= 1 && item->match[item->len - 1] == '/') &&
	    (i = cache_name_pos(item->match, item->len - 1)) >= 0 &&
	    S_ISGITLINK(active_cache[i]->ce_mode)) {
		item->len--;
		match[item->len] = '\0';
	}

	if (flags & PATHSPEC_STRIP_SUBMODULE_SLASH_EXPENSIVE)
		for (i = 0; i < active_nr; i++) {
			struct cache_entry *ce = active_cache[i];
			int ce_len = ce_namelen(ce);

			if (!S_ISGITLINK(ce->ce_mode))
				continue;

			if (item->len <= ce_len || match[ce_len] != '/' ||
			    memcmp(ce->name, match, ce_len))
				continue;
			if (item->len == ce_len + 1) {
				/* strip trailing slash */
				item->len--;
				match[item->len] = '\0';
			} else
				die (_("Pathspec '%s' is in submodule '%.*s'"),
				     elt, ce_len, ce->name);
		}

	if (magic & PATHSPEC_LITERAL)
		item->nowildcard_len = item->len;
	else {
		item->nowildcard_len = simple_length(item->match);
		if (item->nowildcard_len < prefixlen)
			item->nowildcard_len = prefixlen;
	}
	item->flags = 0;
	if (magic & PATHSPEC_GLOB) {
		/*
		 * FIXME: should we enable ONESTAR in _GLOB for
		 * pattern "* * / * . c"?
		 */
	} else {
		if (item->nowildcard_len < item->len &&
		    item->match[item->nowildcard_len] == '*' &&
		    no_wildcard(item->match + item->nowildcard_len + 1))
			item->flags |= PATHSPEC_ONESTAR;
	}

	/* sanity checks, pathspec matchers assume these are sane */
	assert(item->nowildcard_len <= item->len &&
	       item->prefix         <= item->len);
	return magic;
}