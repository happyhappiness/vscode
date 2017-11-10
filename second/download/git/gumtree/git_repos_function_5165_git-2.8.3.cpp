static void mktree_line(char *buf, size_t len, int nul_term_line, int allow_missing)
{
	char *ptr, *ntr;
	unsigned mode;
	enum object_type mode_type; /* object type derived from mode */
	enum object_type obj_type; /* object type derived from sha */
	char *path;
	unsigned char sha1[20];

	ptr = buf;
	/*
	 * Read non-recursive ls-tree output format:
	 *     mode SP type SP sha1 TAB name
	 */
	mode = strtoul(ptr, &ntr, 8);
	if (ptr == ntr || !ntr || *ntr != ' ')
		die("input format error: %s", buf);
	ptr = ntr + 1; /* type */
	ntr = strchr(ptr, ' ');
	if (!ntr || buf + len <= ntr + 40 ||
	    ntr[41] != '\t' ||
	    get_sha1_hex(ntr + 1, sha1))
		die("input format error: %s", buf);

	/* It is perfectly normal if we do not have a commit from a submodule */
	if (S_ISGITLINK(mode))
		allow_missing = 1;


	*ntr++ = 0; /* now at the beginning of SHA1 */

	path = ntr + 41;  /* at the beginning of name */
	if (!nul_term_line && path[0] == '"') {
		struct strbuf p_uq = STRBUF_INIT;
		if (unquote_c_style(&p_uq, path, NULL))
			die("invalid quoting");
		path = strbuf_detach(&p_uq, NULL);
	}

	/*
	 * Object type is redundantly derivable three ways.
	 * These should all agree.
	 */
	mode_type = object_type(mode);
	if (mode_type != type_from_string(ptr)) {
		die("entry '%s' object type (%s) doesn't match mode type (%s)",
			path, ptr, typename(mode_type));
	}

	/* Check the type of object identified by sha1 */
	obj_type = sha1_object_info(sha1, NULL);
	if (obj_type < 0) {
		if (allow_missing) {
			; /* no problem - missing objects are presumed to be of the right type */
		} else {
			die("entry '%s' object %s is unavailable", path, sha1_to_hex(sha1));
		}
	} else {
		if (obj_type != mode_type) {
			/*
			 * The object exists but is of the wrong type.
			 * This is a problem regardless of allow_missing
			 * because the new tree entry will never be correct.
			 */
			die("entry '%s' object %s is a %s but specified type was (%s)",
				path, sha1_to_hex(sha1), typename(obj_type), typename(mode_type));
		}
	}

	append_to_tree(mode, sha1, path);
}