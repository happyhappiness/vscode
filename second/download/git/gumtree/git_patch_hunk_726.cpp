 
 static struct pathspec_magic {
 	unsigned bit;
 	char mnemonic; /* this cannot be ':'! */
 	const char *name;
 } pathspec_magic[] = {
-	{ PATHSPEC_FROMTOP, '/', "top" },
-	{ PATHSPEC_LITERAL,   0, "literal" },
-	{ PATHSPEC_GLOB,   '\0', "glob" },
-	{ PATHSPEC_ICASE,  '\0', "icase" },
-	{ PATHSPEC_EXCLUDE, '!', "exclude" },
+	{ PATHSPEC_FROMTOP,  '/', "top" },
+	{ PATHSPEC_LITERAL, '\0', "literal" },
+	{ PATHSPEC_GLOB,    '\0', "glob" },
+	{ PATHSPEC_ICASE,   '\0', "icase" },
+	{ PATHSPEC_EXCLUDE,  '!', "exclude" },
 };
 
-static void prefix_short_magic(struct strbuf *sb, int prefixlen,
-			       unsigned short_magic)
+static void prefix_magic(struct strbuf *sb, int prefixlen, unsigned magic)
 {
 	int i;
 	strbuf_addstr(sb, ":(");
 	for (i = 0; i < ARRAY_SIZE(pathspec_magic); i++)
-		if (short_magic & pathspec_magic[i].bit) {
+		if (magic & pathspec_magic[i].bit) {
 			if (sb->buf[sb->len - 1] != '(')
 				strbuf_addch(sb, ',');
 			strbuf_addstr(sb, pathspec_magic[i].name);
 		}
 	strbuf_addf(sb, ",prefix:%d)", prefixlen);
 }
 
-/*
- * Take an element of a pathspec and check for magic signatures.
- * Append the result to the prefix. Return the magic bitmap.
- *
- * For now, we only parse the syntax and throw out anything other than
- * "top" magic.
- *
- * NEEDSWORK: This needs to be rewritten when we start migrating
- * get_pathspec() users to use the "struct pathspec" interface.  For
- * example, a pathspec element may be marked as case-insensitive, but
- * the prefix part must always match literally, and a single stupid
- * string cannot express such a case.
- */
-static unsigned prefix_pathspec(struct pathspec_item *item,
-				unsigned *p_short_magic,
-				const char **raw, unsigned flags,
-				const char *prefix, int prefixlen,
-				const char *elt)
-{
-	static int literal_global = -1;
-	static int glob_global = -1;
-	static int noglob_global = -1;
-	static int icase_global = -1;
-	unsigned magic = 0, short_magic = 0, global_magic = 0;
-	const char *copyfrom = elt, *long_magic_end = NULL;
-	char *match;
-	int i, pathspec_prefix = -1;
+static inline int get_literal_global(void)
+{
+	static int literal = -1;
+
+	if (literal < 0)
+		literal = git_env_bool(GIT_LITERAL_PATHSPECS_ENVIRONMENT, 0);
+
+	return literal;
+}
+
+static inline int get_glob_global(void)
+{
+	static int glob = -1;
+
+	if (glob < 0)
+		glob = git_env_bool(GIT_GLOB_PATHSPECS_ENVIRONMENT, 0);
+
+	return glob;
+}
+
+static inline int get_noglob_global(void)
+{
+	static int noglob = -1;
+
+	if (noglob < 0)
+		noglob = git_env_bool(GIT_NOGLOB_PATHSPECS_ENVIRONMENT, 0);
+
+	return noglob;
+}
 
-	if (literal_global < 0)
-		literal_global = git_env_bool(GIT_LITERAL_PATHSPECS_ENVIRONMENT, 0);
-	if (literal_global)
+static inline int get_icase_global(void)
+{
+	static int icase = -1;
+
+	if (icase < 0)
+		icase = git_env_bool(GIT_ICASE_PATHSPECS_ENVIRONMENT, 0);
+
+	return icase;
+}
+
+static int get_global_magic(int element_magic)
+{
+	int global_magic = 0;
+
+	if (get_literal_global())
 		global_magic |= PATHSPEC_LITERAL;
 
-	if (glob_global < 0)
-		glob_global = git_env_bool(GIT_GLOB_PATHSPECS_ENVIRONMENT, 0);
-	if (glob_global)
+	/* --glob-pathspec is overridden by :(literal) */
+	if (get_glob_global() && !(element_magic & PATHSPEC_LITERAL))
 		global_magic |= PATHSPEC_GLOB;
 
-	if (noglob_global < 0)
-		noglob_global = git_env_bool(GIT_NOGLOB_PATHSPECS_ENVIRONMENT, 0);
-
-	if (glob_global && noglob_global)
+	if (get_glob_global() && get_noglob_global())
 		die(_("global 'glob' and 'noglob' pathspec settings are incompatible"));
 
-
-	if (icase_global < 0)
-		icase_global = git_env_bool(GIT_ICASE_PATHSPECS_ENVIRONMENT, 0);
-	if (icase_global)
+	if (get_icase_global())
 		global_magic |= PATHSPEC_ICASE;
 
 	if ((global_magic & PATHSPEC_LITERAL) &&
 	    (global_magic & ~PATHSPEC_LITERAL))
 		die(_("global 'literal' pathspec setting is incompatible "
 		      "with all other global pathspec settings"));
 
-	if (flags & PATHSPEC_LITERAL_PATH)
-		global_magic = 0;
+	/* --noglob-pathspec adds :(literal) _unless_ :(glob) is specified */
+	if (get_noglob_global() && !(element_magic & PATHSPEC_GLOB))
+		global_magic |= PATHSPEC_LITERAL;
 
-	if (elt[0] != ':' || literal_global ||
-	    (flags & PATHSPEC_LITERAL_PATH)) {
-		; /* nothing to do */
-	} else if (elt[1] == '(') {
-		/* longhand */
-		const char *nextat;
-		for (copyfrom = elt + 2;
-		     *copyfrom && *copyfrom != ')';
-		     copyfrom = nextat) {
-			size_t len = strcspn(copyfrom, ",)");
-			if (copyfrom[len] == ',')
-				nextat = copyfrom + len + 1;
-			else
-				/* handle ')' and '\0' */
-				nextat = copyfrom + len;
-			if (!len)
-				continue;
-			for (i = 0; i < ARRAY_SIZE(pathspec_magic); i++) {
-				if (strlen(pathspec_magic[i].name) == len &&
-				    !strncmp(pathspec_magic[i].name, copyfrom, len)) {
-					magic |= pathspec_magic[i].bit;
-					break;
-				}
-				if (starts_with(copyfrom, "prefix:")) {
-					char *endptr;
-					pathspec_prefix = strtol(copyfrom + 7,
-								 &endptr, 10);
-					if (endptr - copyfrom != len)
-						die(_("invalid parameter for pathspec magic 'prefix'"));
-					/* "i" would be wrong, but it does not matter */
-					break;
-				}
+	return global_magic;
+}
+
+/*
+ * Parse the pathspec element looking for long magic
+ *
+ * saves all magic in 'magic'
+ * if prefix magic is used, save the prefix length in 'prefix_len'
+ * returns the position in 'elem' after all magic has been parsed
+ */
+static const char *parse_long_magic(unsigned *magic, int *prefix_len,
+				    const char *elem)
+{
+	const char *pos;
+	const char *nextat;
+
+	for (pos = elem + 2; *pos && *pos != ')'; pos = nextat) {
+		size_t len = strcspn(pos, ",)");
+		int i;
+
+		if (pos[len] == ',')
+			nextat = pos + len + 1; /* handle ',' */
+		else
+			nextat = pos + len; /* handle ')' and '\0' */
+
+		if (!len)
+			continue;
+
+		if (starts_with(pos, "prefix:")) {
+			char *endptr;
+			*prefix_len = strtol(pos + 7, &endptr, 10);
+			if (endptr - pos != len)
+				die(_("invalid parameter for pathspec magic 'prefix'"));
+			continue;
+		}
+
+		for (i = 0; i < ARRAY_SIZE(pathspec_magic); i++) {
+			if (strlen(pathspec_magic[i].name) == len &&
+			    !strncmp(pathspec_magic[i].name, pos, len)) {
+				*magic |= pathspec_magic[i].bit;
+				break;
 			}
-			if (ARRAY_SIZE(pathspec_magic) <= i)
-				die(_("Invalid pathspec magic '%.*s' in '%s'"),
-				    (int) len, copyfrom, elt);
 		}
-		if (*copyfrom != ')')
-			die(_("Missing ')' at the end of pathspec magic in '%s'"), elt);
-		long_magic_end = copyfrom;
-		copyfrom++;
-	} else {
-		/* shorthand */
-		for (copyfrom = elt + 1;
-		     *copyfrom && *copyfrom != ':';
-		     copyfrom++) {
-			char ch = *copyfrom;
 
-			if (!is_pathspec_magic(ch))
+		if (ARRAY_SIZE(pathspec_magic) <= i)
+			die(_("Invalid pathspec magic '%.*s' in '%s'"),
+			    (int) len, pos, elem);
+	}
+
+	if (*pos != ')')
+		die(_("Missing ')' at the end of pathspec magic in '%s'"),
+		    elem);
+	pos++;
+
+	return pos;
+}
+
+/*
+ * Parse the pathspec element looking for short magic
+ *
+ * saves all magic in 'magic'
+ * returns the position in 'elem' after all magic has been parsed
+ */
+static const char *parse_short_magic(unsigned *magic, const char *elem)
+{
+	const char *pos;
+
+	for (pos = elem + 1; *pos && *pos != ':'; pos++) {
+		char ch = *pos;
+		int i;
+
+		if (!is_pathspec_magic(ch))
+			break;
+
+		for (i = 0; i < ARRAY_SIZE(pathspec_magic); i++) {
+			if (pathspec_magic[i].mnemonic == ch) {
+				*magic |= pathspec_magic[i].bit;
 				break;
-			for (i = 0; i < ARRAY_SIZE(pathspec_magic); i++)
-				if (pathspec_magic[i].mnemonic == ch) {
-					short_magic |= pathspec_magic[i].bit;
-					break;
-				}
-			if (ARRAY_SIZE(pathspec_magic) <= i)
-				die(_("Unimplemented pathspec magic '%c' in '%s'"),
-				    ch, elt);
+			}
 		}
-		if (*copyfrom == ':')
-			copyfrom++;
+
+		if (ARRAY_SIZE(pathspec_magic) <= i)
+			die(_("Unimplemented pathspec magic '%c' in '%s'"),
+			    ch, elem);
 	}
 
-	magic |= short_magic;
-	*p_short_magic = short_magic;
+	if (*pos == ':')
+		pos++;
 
-	/* --noglob-pathspec adds :(literal) _unless_ :(glob) is specified */
-	if (noglob_global && !(magic & PATHSPEC_GLOB))
-		global_magic |= PATHSPEC_LITERAL;
+	return pos;
+}
 
-	/* --glob-pathspec is overridden by :(literal) */
-	if ((global_magic & PATHSPEC_GLOB) && (magic & PATHSPEC_LITERAL))
-		global_magic &= ~PATHSPEC_GLOB;
+static const char *parse_element_magic(unsigned *magic, int *prefix_len,
+				       const char *elem)
+{
+	if (elem[0] != ':' || get_literal_global())
+		return elem; /* nothing to do */
+	else if (elem[1] == '(')
+		/* longhand */
+		return parse_long_magic(magic, prefix_len, elem);
+	else
+		/* shorthand */
+		return parse_short_magic(magic, elem);
+}
 
-	magic |= global_magic;
+static void strip_submodule_slash_cheap(struct pathspec_item *item)
+{
+	if (item->len >= 1 && item->match[item->len - 1] == '/') {
+		int i = cache_name_pos(item->match, item->len - 1);
+
+		if (i >= 0 && S_ISGITLINK(active_cache[i]->ce_mode)) {
+			item->len--;
+			item->match[item->len] = '\0';
+		}
+	}
+}
+
+static void strip_submodule_slash_expensive(struct pathspec_item *item)
+{
+	int i;
+
+	for (i = 0; i < active_nr; i++) {
+		struct cache_entry *ce = active_cache[i];
+		int ce_len = ce_namelen(ce);
+
+		if (!S_ISGITLINK(ce->ce_mode))
+			continue;
+
+		if (item->len <= ce_len || item->match[ce_len] != '/' ||
+		    memcmp(ce->name, item->match, ce_len))
+			continue;
+
+		if (item->len == ce_len + 1) {
+			/* strip trailing slash */
+			item->len--;
+			item->match[item->len] = '\0';
+		} else {
+			die(_("Pathspec '%s' is in submodule '%.*s'"),
+			    item->original, ce_len, ce->name);
+		}
+	}
+}
+
+static void die_inside_submodule_path(struct pathspec_item *item)
+{
+	int i;
+
+	for (i = 0; i < active_nr; i++) {
+		struct cache_entry *ce = active_cache[i];
+		int ce_len = ce_namelen(ce);
+
+		if (!S_ISGITLINK(ce->ce_mode))
+			continue;
+
+		if (item->len < ce_len ||
+		    !(item->match[ce_len] == '/' || item->match[ce_len] == '\0') ||
+		    memcmp(ce->name, item->match, ce_len))
+			continue;
+
+		die(_("Pathspec '%s' is in submodule '%.*s'"),
+		    item->original, ce_len, ce->name);
+	}
+}
+
+/*
+ * Perform the initialization of a pathspec_item based on a pathspec element.
+ */
+static void init_pathspec_item(struct pathspec_item *item, unsigned flags,
+			       const char *prefix, int prefixlen,
+			       const char *elt)
+{
+	unsigned magic = 0, element_magic = 0;
+	const char *copyfrom = elt;
+	char *match;
+	int pathspec_prefix = -1;
+
+	/* PATHSPEC_LITERAL_PATH ignores magic */
+	if (flags & PATHSPEC_LITERAL_PATH) {
+		magic = PATHSPEC_LITERAL;
+	} else {
+		copyfrom = parse_element_magic(&element_magic,
+					       &pathspec_prefix,
+					       elt);
+		magic |= element_magic;
+		magic |= get_global_magic(element_magic);
+	}
+
+	item->magic = magic;
 
 	if (pathspec_prefix >= 0 &&
 	    (prefixlen || (prefix && *prefix)))
 		die("BUG: 'prefix' magic is supposed to be used at worktree's root");
 
 	if ((magic & PATHSPEC_LITERAL) && (magic & PATHSPEC_GLOB))
 		die(_("%s: 'literal' and 'glob' are incompatible"), elt);
 
+	/* Create match string which will be used for pathspec matching */
 	if (pathspec_prefix >= 0) {
 		match = xstrdup(copyfrom);
 		prefixlen = pathspec_prefix;
 	} else if (magic & PATHSPEC_FROMTOP) {
 		match = xstrdup(copyfrom);
 		prefixlen = 0;
 	} else {
-		match = prefix_path_gently(prefix, prefixlen, &prefixlen, copyfrom);
+		match = prefix_path_gently(prefix, prefixlen,
+					   &prefixlen, copyfrom);
 		if (!match)
 			die(_("%s: '%s' is outside repository"), elt, copyfrom);
 	}
-	*raw = item->match = match;
+
+	item->match = match;
+	item->len = strlen(item->match);
+	item->prefix = prefixlen;
+
 	/*
 	 * Prefix the pathspec (keep all magic) and assign to
 	 * original. Useful for passing to another command.
 	 */
-	if (flags & PATHSPEC_PREFIX_ORIGIN) {
+	if ((flags & PATHSPEC_PREFIX_ORIGIN) &&
+	    prefixlen && !get_literal_global()) {
 		struct strbuf sb = STRBUF_INIT;
-		if (prefixlen && !literal_global) {
-			/* Preserve the actual prefix length of each pattern */
-			if (short_magic)
-				prefix_short_magic(&sb, prefixlen, short_magic);
-			else if (long_magic_end) {
-				strbuf_add(&sb, elt, long_magic_end - elt);
-				strbuf_addf(&sb, ",prefix:%d)", prefixlen);
-			} else
-				strbuf_addf(&sb, ":(prefix:%d)", prefixlen);
-		}
+
+		/* Preserve the actual prefix length of each pattern */
+		prefix_magic(&sb, prefixlen, element_magic);
+
 		strbuf_addstr(&sb, match);
 		item->original = strbuf_detach(&sb, NULL);
-	} else
-		item->original = elt;
-	item->len = strlen(item->match);
-	item->prefix = prefixlen;
-
-	if ((flags & PATHSPEC_STRIP_SUBMODULE_SLASH_CHEAP) &&
-	    (item->len >= 1 && item->match[item->len - 1] == '/') &&
-	    (i = cache_name_pos(item->match, item->len - 1)) >= 0 &&
-	    S_ISGITLINK(active_cache[i]->ce_mode)) {
-		item->len--;
-		match[item->len] = '\0';
+	} else {
+		item->original = xstrdup(elt);
 	}
 
+	if (flags & PATHSPEC_STRIP_SUBMODULE_SLASH_CHEAP)
+		strip_submodule_slash_cheap(item);
+
 	if (flags & PATHSPEC_STRIP_SUBMODULE_SLASH_EXPENSIVE)
-		for (i = 0; i < active_nr; i++) {
-			struct cache_entry *ce = active_cache[i];
-			int ce_len = ce_namelen(ce);
-
-			if (!S_ISGITLINK(ce->ce_mode))
-				continue;
-
-			if (item->len <= ce_len || match[ce_len] != '/' ||
-			    memcmp(ce->name, match, ce_len))
-				continue;
-			if (item->len == ce_len + 1) {
-				/* strip trailing slash */
-				item->len--;
-				match[item->len] = '\0';
-			} else
-				die (_("Pathspec '%s' is in submodule '%.*s'"),
-				     elt, ce_len, ce->name);
-		}
+		strip_submodule_slash_expensive(item);
 
-	if (magic & PATHSPEC_LITERAL)
+	if (magic & PATHSPEC_LITERAL) {
 		item->nowildcard_len = item->len;
-	else {
+	} else {
 		item->nowildcard_len = simple_length(item->match);
 		if (item->nowildcard_len < prefixlen)
 			item->nowildcard_len = prefixlen;
 	}
+
 	item->flags = 0;
 	if (magic & PATHSPEC_GLOB) {
 		/*
 		 * FIXME: should we enable ONESTAR in _GLOB for
 		 * pattern "* * / * . c"?
 		 */
