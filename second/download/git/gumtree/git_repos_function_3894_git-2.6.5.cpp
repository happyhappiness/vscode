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
			die(_("%s: '%s' is outside repository"), elt, copyfrom