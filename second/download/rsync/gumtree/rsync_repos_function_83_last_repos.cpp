static char *parse_merge_name(const char *merge_file, unsigned int *len_ptr,
			      unsigned int prefix_skip)
{
	static char buf[MAXPATHLEN];
	char *fn, tmpbuf[MAXPATHLEN];
	unsigned int fn_len;

	if (!parent_dirscan && *merge_file != '/') {
		/* Return the name unchanged it doesn't have any slashes. */
		if (len_ptr) {
			const char *p = merge_file + *len_ptr;
			while (--p > merge_file && *p != '/') {}
			if (p == merge_file) {
				strlcpy(buf, merge_file, *len_ptr + 1);
				return buf;
			}
		} else if (strchr(merge_file, '/') == NULL)
			return (char *)merge_file;
	}

	fn = *merge_file == '/' ? buf : tmpbuf;
	if (sanitize_paths) {
		const char *r = prefix_skip ? "/" : NULL;
		/* null-terminate the name if it isn't already */
		if (len_ptr && merge_file[*len_ptr]) {
			char *to = fn == buf ? tmpbuf : buf;
			strlcpy(to, merge_file, *len_ptr + 1);
			merge_file = to;
		}
		if (!sanitize_path(fn, merge_file, r, dirbuf_depth, SP_DEFAULT)) {
			rprintf(FERROR, "merge-file name overflows: %s\n",
				merge_file);
			return NULL;
		}
		fn_len = strlen(fn);
	} else {
		strlcpy(fn, merge_file, len_ptr ? *len_ptr + 1 : MAXPATHLEN);
		fn_len = clean_fname(fn, CFN_COLLAPSE_DOT_DOT_DIRS);
	}

	/* If the name isn't in buf yet, it wasn't absolute. */
	if (fn != buf) {
		int d_len = dirbuf_len - prefix_skip;
		if (d_len + fn_len >= MAXPATHLEN) {
			rprintf(FERROR, "merge-file name overflows: %s\n", fn);
			return NULL;
		}
		memcpy(buf, dirbuf + prefix_skip, d_len);
		memcpy(buf + d_len, fn, fn_len + 1);
		fn_len = clean_fname(buf, CFN_COLLAPSE_DOT_DOT_DIRS);
	}

	if (len_ptr)
		*len_ptr = fn_len;
	return buf;
}