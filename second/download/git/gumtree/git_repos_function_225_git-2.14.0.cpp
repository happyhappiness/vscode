static void show_patch_diff(struct combine_diff_path *elem, int num_parent,
			    int dense, int working_tree_file,
			    struct rev_info *rev)
{
	struct diff_options *opt = &rev->diffopt;
	unsigned long result_size, cnt, lno;
	int result_deleted = 0;
	char *result, *cp;
	struct sline *sline; /* survived lines */
	int mode_differs = 0;
	int i, show_hunks;
	mmfile_t result_file;
	struct userdiff_driver *userdiff;
	struct userdiff_driver *textconv = NULL;
	int is_binary;
	const char *line_prefix = diff_line_prefix(opt);

	context = opt->context;
	userdiff = userdiff_find_by_path(elem->path);
	if (!userdiff)
		userdiff = userdiff_find_by_name("default");
	if (DIFF_OPT_TST(opt, ALLOW_TEXTCONV))
		textconv = userdiff_get_textconv(userdiff);

	/* Read the result of merge first */
	if (!working_tree_file)
		result = grab_blob(&elem->oid, elem->mode, &result_size,
				   textconv, elem->path);
	else {
		/* Used by diff-tree to read from the working tree */
		struct stat st;
		int fd = -1;

		if (lstat(elem->path, &st) < 0)
			goto deleted_file;

		if (S_ISLNK(st.st_mode)) {
			struct strbuf buf = STRBUF_INIT;

			if (strbuf_readlink(&buf, elem->path, st.st_size) < 0) {
				error_errno("readlink(%s)", elem->path);
				return;
			}
			result_size = buf.len;
			result = strbuf_detach(&buf, NULL);
			elem->mode = canon_mode(st.st_mode);
		} else if (S_ISDIR(st.st_mode)) {
			struct object_id oid;
			if (resolve_gitlink_ref(elem->path, "HEAD", oid.hash) < 0)
				result = grab_blob(&elem->oid, elem->mode,
						   &result_size, NULL, NULL);
			else
				result = grab_blob(&oid, elem->mode,
						   &result_size, NULL, NULL);
		} else if (textconv) {
			struct diff_filespec *df = alloc_filespec(elem->path);
			fill_filespec(df, &null_oid, 0, st.st_mode);
			result_size = fill_textconv(textconv, df, &result);
			free_filespec(df);
		} else if (0 <= (fd = open(elem->path, O_RDONLY))) {
			size_t len = xsize_t(st.st_size);
			ssize_t done;
			int is_file, i;

			elem->mode = canon_mode(st.st_mode);
			/* if symlinks don't work, assume symlink if all parents
			 * are symlinks
			 */
			is_file = has_symlinks;
			for (i = 0; !is_file && i < num_parent; i++)
				is_file = !S_ISLNK(elem->parent[i].mode);
			if (!is_file)
				elem->mode = canon_mode(S_IFLNK);

			result_size = len;
			result = xmallocz(len);

			done = read_in_full(fd, result, len);
			if (done < 0)
				die_errno("read error '%s'", elem->path);
			else if (done < len)
				die("early EOF '%s'", elem->path);

			/* If not a fake symlink, apply filters, e.g. autocrlf */
			if (is_file) {
				struct strbuf buf = STRBUF_INIT;

				if (convert_to_git(&the_index, elem->path, result, len, &buf, safe_crlf)) {
					free(result);
					result = strbuf_detach(&buf, &len);
					result_size = len;
				}
			}
		}
		else {
		deleted_file:
			result_deleted = 1;
			result_size = 0;
			elem->mode = 0;
			result = xcalloc(1, 1);
		}

		if (0 <= fd)
			close(fd);
	}

	for (i = 0; i < num_parent; i++) {
		if (elem->parent[i].mode != elem->mode) {
			mode_differs = 1;
			break;
		}
	}

	if (textconv)
		is_binary = 0;
	else if (userdiff->binary != -1)
		is_binary = userdiff->binary;
	else {
		is_binary = buffer_is_binary(result, result_size);
		for (i = 0; !is_binary && i < num_parent; i++) {
			char *buf;
			unsigned long size;
			buf = grab_blob(&elem->parent[i].oid,
					elem->parent[i].mode,
					&size, NULL, NULL);
			if (buffer_is_binary(buf, size))
				is_binary = 1;
			free(buf);
		}
	}
	if (is_binary) {
		show_combined_header(elem, num_parent, dense, rev,
				     line_prefix, mode_differs, 0);
		printf("Binary files differ\n");
		free(result);
		return;
	}

	for (cnt = 0, cp = result; cp < result + result_size; cp++) {
		if (*cp == '\n')
			cnt++;
	}
	if (result_size && result[result_size-1] != '\n')
		cnt++; /* incomplete line */

	sline = xcalloc(st_add(cnt, 2), sizeof(*sline));
	sline[0].bol = result;
	for (lno = 0, cp = result; cp < result + result_size; cp++) {
		if (*cp == '\n') {
			sline[lno].len = cp - sline[lno].bol;
			lno++;
			if (lno < cnt)
				sline[lno].bol = cp + 1;
		}
	}
	if (result_size && result[result_size-1] != '\n')
		sline[cnt-1].len = result_size - (sline[cnt-1].bol - result);

	result_file.ptr = result;
	result_file.size = result_size;

	/* Even p_lno[cnt+1] is valid -- that is for the end line number
	 * for deletion hunk at the end.
	 */
	sline[0].p_lno = xcalloc(st_mult(st_add(cnt, 2), num_parent), sizeof(unsigned long));
	for (lno = 0; lno <= cnt; lno++)
		sline[lno+1].p_lno = sline[lno].p_lno + num_parent;

	for (i = 0; i < num_parent; i++) {
		int j;
		for (j = 0; j < i; j++) {
			if (!oidcmp(&elem->parent[i].oid,
				     &elem->parent[j].oid)) {
				reuse_combine_diff(sline, cnt, i, j);
				break;
			}
		}
		if (i <= j)
			combine_diff(&elem->parent[i].oid,
				     elem->parent[i].mode,
				     &result_file, sline,
				     cnt, i, num_parent, result_deleted,
				     textconv, elem->path, opt->xdl_opts);
	}

	show_hunks = make_hunks(sline, cnt, num_parent, dense);

	if (show_hunks || mode_differs || working_tree_file) {
		show_combined_header(elem, num_parent, dense, rev,
				     line_prefix, mode_differs, 1);
		dump_sline(sline, line_prefix, cnt, num_parent,
			   opt->use_color, result_deleted);
	}
	free(result);

	for (lno = 0; lno < cnt; lno++) {
		if (sline[lno].lost) {
			struct lline *ll = sline[lno].lost;
			while (ll) {
				struct lline *tmp = ll;
				ll = ll->next;
				free(tmp);
			}
		}
	}
	free(sline[0].p_lno);
	free(sline);
}