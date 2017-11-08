static void read_index_info(int nul_term_line)
{
	struct strbuf buf = STRBUF_INIT;
	struct strbuf uq = STRBUF_INIT;
	strbuf_getline_fn getline_fn;

	getline_fn = nul_term_line ? strbuf_getline_nul : strbuf_getline_lf;
	while (getline_fn(&buf, stdin) != EOF) {
		char *ptr, *tab;
		char *path_name;
		struct object_id oid;
		unsigned int mode;
		unsigned long ul;
		int stage;

		/* This reads lines formatted in one of three formats:
		 *
		 * (1) mode         SP sha1          TAB path
		 * The first format is what "git apply --index-info"
		 * reports, and used to reconstruct a partial tree
		 * that is used for phony merge base tree when falling
		 * back on 3-way merge.
		 *
		 * (2) mode SP type SP sha1          TAB path
		 * The second format is to stuff "git ls-tree" output
		 * into the index file.
		 *
		 * (3) mode         SP sha1 SP stage TAB path
		 * This format is to put higher order stages into the
		 * index file and matches "git ls-files --stage" output.
		 */
		errno = 0;
		ul = strtoul(buf.buf, &ptr, 8);
		if (ptr == buf.buf || *ptr != ' '
		    || errno || (unsigned int) ul != ul)
			goto bad_line;
		mode = ul;

		tab = strchr(ptr, '\t');
		if (!tab || tab - ptr < GIT_SHA1_HEXSZ + 1)
			goto bad_line;

		if (tab[-2] == ' ' && '0' <= tab[-1] && tab[-1] <= '3') {
			stage = tab[-1] - '0';
			ptr = tab + 1; /* point at the head of path */
			tab = tab - 2; /* point at tail of sha1 */
		}
		else {
			stage = 0;
			ptr = tab + 1; /* point at the head of path */
		}

		if (get_oid_hex(tab - GIT_SHA1_HEXSZ, &oid) ||
			tab[-(GIT_SHA1_HEXSZ + 1)] != ' ')
			goto bad_line;

		path_name = ptr;
		if (!nul_term_line && path_name[0] == '"') {
			strbuf_reset(&uq);
			if (unquote_c_style(&uq, path_name, NULL)) {
				die("git update-index: bad quoting of path name");
			}
			path_name = uq.buf;
		}

		if (!verify_path(path_name)) {
			fprintf(stderr, "Ignoring path %s\n", path_name);
			continue;
		}

		if (!mode) {
			/* mode == 0 means there is no such path -- remove */
			if (remove_file_from_cache(path_name))
				die("git update-index: unable to remove %s",
				    ptr);
		}
		else {
			/* mode ' ' sha1 '\t' name
			 * ptr[-1] points at tab,
			 * ptr[-41] is at the beginning of sha1
			 */
			ptr[-(GIT_SHA1_HEXSZ + 2)] = ptr[-1] = 0;
			if (add_cacheinfo(mode, &oid, path_name, stage))
				die("git update-index: unable to update %s",
				    path_name);
		}
		continue;

	bad_line:
		die("malformed index info %s", buf.buf);
	}
	strbuf_release(&buf);
	strbuf_release(&uq);
}