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
		if (!sanitize_path(fn, merge_file, r, dirbuf_depth)) {
			rprintf(FERROR, "merge-file name overflows: %s\n",
				safe_fname(merge_file));
			return NULL;
		}
	} else {
		strlcpy(fn, merge_file, len_ptr ? *len_ptr + 1 : MAXPATHLEN);
		clean_fname(fn, 1);
	}
	
	fn_len = strlen(fn);
	if (fn == buf)
		goto done;

	if (dirbuf_len + fn_len >= MAXPATHLEN) {
		rprintf(FERROR, "merge-file name overflows: %s\n",
			safe_fname(fn));
		return NULL;
	}
	memcpy(buf, dirbuf + prefix_skip, dirbuf_len - prefix_skip);
	memcpy(buf + dirbuf_len - prefix_skip, fn, fn_len + 1);
	fn_len = clean_fname(buf, 1);

    done:
	if (len_ptr)
		*len_ptr = fn_len;
	return buf;
}