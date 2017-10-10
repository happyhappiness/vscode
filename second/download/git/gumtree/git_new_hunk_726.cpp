
static struct pathspec_magic {
	unsigned bit;
	char mnemonic; /* this cannot be ':'! */
	const char *name;
} pathspec_magic[] = {
	{ PATHSPEC_FROMTOP,  '/', "top" },
	{ PATHSPEC_LITERAL, '\0', "literal" },
	{ PATHSPEC_GLOB,    '\0', "glob" },
	{ PATHSPEC_ICASE,   '\0', "icase" },
	{ PATHSPEC_EXCLUDE,  '!', "exclude" },
};

static void prefix_magic(struct strbuf *sb, int prefixlen, unsigned magic)
{
	int i;
	strbuf_addstr(sb, ":(");
	for (i = 0; i < ARRAY_SIZE(pathspec_magic); i++)
		if (magic & pathspec_magic[i].bit) {
			if (sb->buf[sb->len - 1] != '(')
				strbuf_addch(sb, ',');
			strbuf_addstr(sb, pathspec_magic[i].name);
		}
	strbuf_addf(sb, ",prefix:%d)", prefixlen);
}

static inline int get_literal_global(void)
{
	static int literal = -1;

	if (literal < 0)
		literal = git_env_bool(GIT_LITERAL_PATHSPECS_ENVIRONMENT, 0);

	return literal;
}

static inline int get_glob_global(void)
{
	static int glob = -1;

	if (glob < 0)
		glob = git_env_bool(GIT_GLOB_PATHSPECS_ENVIRONMENT, 0);

	return glob;
}

static inline int get_noglob_global(void)
{
	static int noglob = -1;

	if (noglob < 0)
		noglob = git_env_bool(GIT_NOGLOB_PATHSPECS_ENVIRONMENT, 0);

	return noglob;
}

static inline int get_icase_global(void)
{
	static int icase = -1;

	if (icase < 0)
		icase = git_env_bool(GIT_ICASE_PATHSPECS_ENVIRONMENT, 0);

	return icase;
}

static int get_global_magic(int element_magic)
{
	int global_magic = 0;

	if (get_literal_global())
		global_magic |= PATHSPEC_LITERAL;

	/* --glob-pathspec is overridden by :(literal) */
	if (get_glob_global() && !(element_magic & PATHSPEC_LITERAL))
		global_magic |= PATHSPEC_GLOB;

	if (get_glob_global() && get_noglob_global())
		die(_("global 'glob' and 'noglob' pathspec settings are incompatible"));

	if (get_icase_global())
		global_magic |= PATHSPEC_ICASE;

	if ((global_magic & PATHSPEC_LITERAL) &&
	    (global_magic & ~PATHSPEC_LITERAL))
		die(_("global 'literal' pathspec setting is incompatible "
		      "with all other global pathspec settings"));

	/* --noglob-pathspec adds :(literal) _unless_ :(glob) is specified */
	if (get_noglob_global() && !(element_magic & PATHSPEC_GLOB))
		global_magic |= PATHSPEC_LITERAL;

	return global_magic;
}

/*
 * Parse the pathspec element looking for long magic
 *
 * saves all magic in 'magic'
 * if prefix magic is used, save the prefix length in 'prefix_len'
 * returns the position in 'elem' after all magic has been parsed
 */
static const char *parse_long_magic(unsigned *magic, int *prefix_len,
				    const char *elem)
{
	const char *pos;
	const char *nextat;

	for (pos = elem + 2; *pos && *pos != ')'; pos = nextat) {
		size_t len = strcspn(pos, ",)");
		int i;

		if (pos[len] == ',')
			nextat = pos + len + 1; /* handle ',' */
		else
			nextat = pos + len; /* handle ')' and '\0' */

		if (!len)
			continue;

		if (starts_with(pos, "prefix:")) {
			char *endptr;
			*prefix_len = strtol(pos + 7, &endptr, 10);
			if (endptr - pos != len)
				die(_("invalid parameter for pathspec magic 'prefix'"));
			continue;
		}

		for (i = 0; i < ARRAY_SIZE(pathspec_magic); i++) {
			if (strlen(pathspec_magic[i].name) == len &&
			    !strncmp(pathspec_magic[i].name, pos, len)) {
				*magic |= pathspec_magic[i].bit;
				break;
			}
		}

		if (ARRAY_SIZE(pathspec_magic) <= i)
			die(_("Invalid pathspec magic '%.*s' in '%s'"),
			    (int) len, pos, elem);
	}

	if (*pos != ')')
		die(_("Missing ')' at the end of pathspec magic in '%s'"),
		    elem);
	pos++;

	return pos;
}

/*
 * Parse the pathspec element looking for short magic
 *
 * saves all magic in 'magic'
 * returns the position in 'elem' after all magic has been parsed
 */
static const char *parse_short_magic(unsigned *magic, const char *elem)
{
	const char *pos;

	for (pos = elem + 1; *pos && *pos != ':'; pos++) {
		char ch = *pos;
		int i;

		if (!is_pathspec_magic(ch))
			break;

		for (i = 0; i < ARRAY_SIZE(pathspec_magic); i++) {
			if (pathspec_magic[i].mnemonic == ch) {
				*magic |= pathspec_magic[i].bit;
				break;
			}
		}

		if (ARRAY_SIZE(pathspec_magic) <= i)
			die(_("Unimplemented pathspec magic '%c' in '%s'"),
			    ch, elem);
	}

	if (*pos == ':')
		pos++;

	return pos;
}

static const char *parse_element_magic(unsigned *magic, int *prefix_len,
				       const char *elem)
{
	if (elem[0] != ':' || get_literal_global())
		return elem; /* nothing to do */
	else if (elem[1] == '(')
		/* longhand */
		return parse_long_magic(magic, prefix_len, elem);
	else
		/* shorthand */
		return parse_short_magic(magic, elem);
}

static void strip_submodule_slash_cheap(struct pathspec_item *item)
{
	if (item->len >= 1 && item->match[item->len - 1] == '/') {
		int i = cache_name_pos(item->match, item->len - 1);

		if (i >= 0 && S_ISGITLINK(active_cache[i]->ce_mode)) {
			item->len--;
			item->match[item->len] = '\0';
		}
	}
}

static void strip_submodule_slash_expensive(struct pathspec_item *item)
{
	int i;

	for (i = 0; i < active_nr; i++) {
		struct cache_entry *ce = active_cache[i];
		int ce_len = ce_namelen(ce);

		if (!S_ISGITLINK(ce->ce_mode))
			continue;

		if (item->len <= ce_len || item->match[ce_len] != '/' ||
		    memcmp(ce->name, item->match, ce_len))
			continue;

		if (item->len == ce_len + 1) {
			/* strip trailing slash */
			item->len--;
			item->match[item->len] = '\0';
		} else {
			die(_("Pathspec '%s' is in submodule '%.*s'"),
			    item->original, ce_len, ce->name);
		}
	}
}

static void die_inside_submodule_path(struct pathspec_item *item)
{
	int i;

	for (i = 0; i < active_nr; i++) {
		struct cache_entry *ce = active_cache[i];
		int ce_len = ce_namelen(ce);

		if (!S_ISGITLINK(ce->ce_mode))
			continue;

		if (item->len < ce_len ||
		    !(item->match[ce_len] == '/' || item->match[ce_len] == '\0') ||
		    memcmp(ce->name, item->match, ce_len))
			continue;

		die(_("Pathspec '%s' is in submodule '%.*s'"),
		    item->original, ce_len, ce->name);
	}
}

/*
 * Perform the initialization of a pathspec_item based on a pathspec element.
 */
static void init_pathspec_item(struct pathspec_item *item, unsigned flags,
			       const char *prefix, int prefixlen,
			       const char *elt)
{
	unsigned magic = 0, element_magic = 0;
	const char *copyfrom = elt;
	char *match;
	int pathspec_prefix = -1;

	/* PATHSPEC_LITERAL_PATH ignores magic */
	if (flags & PATHSPEC_LITERAL_PATH) {
		magic = PATHSPEC_LITERAL;
	} else {
		copyfrom = parse_element_magic(&element_magic,
					       &pathspec_prefix,
					       elt);
		magic |= element_magic;
		magic |= get_global_magic(element_magic);
	}

	item->magic = magic;

	if (pathspec_prefix >= 0 &&
	    (prefixlen || (prefix && *prefix)))
		die("BUG: 'prefix' magic is supposed to be used at worktree's root");

	if ((magic & PATHSPEC_LITERAL) && (magic & PATHSPEC_GLOB))
		die(_("%s: 'literal' and 'glob' are incompatible"), elt);

	/* Create match string which will be used for pathspec matching */
	if (pathspec_prefix >= 0) {
		match = xstrdup(copyfrom);
		prefixlen = pathspec_prefix;
	} else if (magic & PATHSPEC_FROMTOP) {
		match = xstrdup(copyfrom);
		prefixlen = 0;
	} else {
		match = prefix_path_gently(prefix, prefixlen,
					   &prefixlen, copyfrom);
		if (!match)
			die(_("%s: '%s' is outside repository"), elt, copyfrom);
	}

	item->match = match;
	item->len = strlen(item->match);
	item->prefix = prefixlen;

	/*
	 * Prefix the pathspec (keep all magic) and assign to
	 * original. Useful for passing to another command.
	 */
	if ((flags & PATHSPEC_PREFIX_ORIGIN) &&
	    prefixlen && !get_literal_global()) {
		struct strbuf sb = STRBUF_INIT;

		/* Preserve the actual prefix length of each pattern */
		prefix_magic(&sb, prefixlen, element_magic);

		strbuf_addstr(&sb, match);
		item->original = strbuf_detach(&sb, NULL);
	} else {
		item->original = xstrdup(elt);
	}

	if (flags & PATHSPEC_STRIP_SUBMODULE_SLASH_CHEAP)
		strip_submodule_slash_cheap(item);

	if (flags & PATHSPEC_STRIP_SUBMODULE_SLASH_EXPENSIVE)
		strip_submodule_slash_expensive(item);

	if (magic & PATHSPEC_LITERAL) {
		item->nowildcard_len = item->len;
	} else {
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
