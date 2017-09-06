static struct tree *
tree_reopen(struct tree *t, const wchar_t *path, int restore_time)
{
	struct archive_wstring ws;
	wchar_t *pathname, *p, *base;

	t->flags = (restore_time)?needsRestoreTimes:0;
	t->visit_type = 0;
	t->tree_errno = 0;
	t->full_path_dir_length = 0;
	t->dirname_length = 0;
	t->depth = 0;
	t->descend = 0;
	t->current = NULL;
	t->d = INVALID_HANDLE_VALUE;
	t->symlink_mode = t->initial_symlink_mode;
	archive_string_empty(&(t->full_path));
	archive_string_empty(&t->path);
	t->entry_fh = INVALID_HANDLE_VALUE;
	t->entry_eof = 0;
	t->entry_remaining_bytes = 0;
	t->initial_filesystem_id = -1;

	/* Get wchar_t strings from char strings. */
	archive_string_init(&ws);
	archive_wstrcpy(&ws, path);
	pathname = ws.s;
	/* Get a full-path-name. */
	p = __la_win_permissive_name_w(pathname);
	if (p == NULL)
		goto failed;
	archive_wstrcpy(&(t->full_path), p);
	free(p);

	/* Convert path separators from '\' to '/' */
	for (p = pathname; *p != L'\0'; ++p) {
		if (*p == L'\\')
			*p = L'/';
	}
	base = pathname;

	/* First item is set up a lot like a symlink traversal. */
	/* printf("Looking for wildcard in %s\n", path); */
	if ((base[0] == L'/' && base[1] == L'/' &&
	     base[2] == L'?' && base[3] == L'/' &&
	     (wcschr(base+4, L'*') || wcschr(base+4, L'?'))) ||
	    (!(base[0] == L'/' && base[1] == L'/' &&
	       base[2] == L'?' && base[3] == L'/') &&
	       (wcschr(base, L'*') || wcschr(base, L'?')))) {
		// It has a wildcard in it...
		// Separate the last element.
		p = wcsrchr(base, L'/');
		if (p != NULL) {
			*p = L'\0';
			tree_append(t, base, p - base);
			t->dirname_length = archive_strlen(&t->path);
			base = p + 1;
		}
		p = wcsrchr(t->full_path.s, L'\\');
		if (p != NULL) {
			*p = L'\0';
			t->full_path.length = wcslen(t->full_path.s);
			t->full_path_dir_length = archive_strlen(&t->full_path);
		}
	}
	tree_push(t, base, t->full_path.s, 0, 0, 0, NULL);
	archive_wstring_free(&ws);
	t->stack->flags = needsFirstVisit;
	/*
	 * Debug flag for Direct IO(No buffering) or Async IO.
	 * Those dependant on environment variable switches
	 * will be removed until next release.
	 */
	{
		const char *e;
		if ((e = getenv("LIBARCHIVE_DIRECT_IO")) != NULL) {
			if (e[0] == '0')
				t->direct_io = 0;
			else
				t->direct_io = 1;
			fprintf(stderr, "LIBARCHIVE_DIRECT_IO=%s\n",
				(t->direct_io)?"Enabled":"Disabled");
		} else
			t->direct_io = DIRECT_IO;
		if ((e = getenv("LIBARCHIVE_ASYNC_IO")) != NULL) {
			if (e[0] == '0')
				t->async_io = 0;
			else
				t->async_io = 1;
			fprintf(stderr, "LIBARCHIVE_ASYNC_IO=%s\n",
			    (t->async_io)?"Enabled":"Disabled");
		} else
			t->async_io = ASYNC_IO;
	}
	return (t);
failed:
	archive_wstring_free(&ws);
	tree_free(t);
	return (NULL);
}