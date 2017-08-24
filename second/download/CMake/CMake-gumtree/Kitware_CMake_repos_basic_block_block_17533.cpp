{
#if defined(_WIN32) && !defined(__CYGWIN__)
	char name[_MAX_FNAME];/* Included null terminator size. */
#elif defined(NAME_MAX) && NAME_MAX >= 255
	char name[NAME_MAX+1];
#else
	char name[256];
#endif
	struct xar *xar = (struct xar *)a->format_data;
	struct file *dent, *file, *np;
	struct archive_entry *ent;
	const char *fn, *p;
	int l;

	file = *filepp;
	dent = xar->root;
	if (file->parentdir.length > 0)
		fn = p = file->parentdir.s;
	else
		fn = p = "";

	/*
	 * If the path of the parent directory of `file' entry is
	 * the same as the path of `cur_dirent', add isoent to
	 * `cur_dirent'.
	 */
	if (archive_strlen(&(xar->cur_dirstr))
	      == archive_strlen(&(file->parentdir)) &&
	    strcmp(xar->cur_dirstr.s, fn) == 0) {
		if (!file_add_child_tail(xar->cur_dirent, file)) {
			np = (struct file *)__archive_rb_tree_find_node(
			    &(xar->cur_dirent->rbtree),
			    file->basename.s);
			goto same_entry;
		}
		return (ARCHIVE_OK);
	}

	for (;;) {
		l = get_path_component(name, sizeof(name), fn);
		if (l == 0) {
			np = NULL;
			break;
		}
		if (l < 0) {
			archive_set_error(&a->archive,
			    ARCHIVE_ERRNO_MISC,
			    "A name buffer is too small");
			file_free(file);
			*filepp = NULL;
			return (ARCHIVE_FATAL);
		}

		np = file_find_child(dent, name);
		if (np == NULL || fn[0] == '\0')
			break;

		/* Find next subdirectory. */
		if (!np->dir) {
			/* NOT Directory! */
			archive_set_error(&a->archive,
			    ARCHIVE_ERRNO_MISC,
			    "`%s' is not directory, we cannot insert `%s' ",
			    archive_entry_pathname(np->entry),
			    archive_entry_pathname(file->entry));
			file_free(file);
			*filepp = NULL;
			return (ARCHIVE_FAILED);
		}
		fn += l;
		if (fn[0] == '/')
			fn++;
		dent = np;
	}
	if (np == NULL) {
		/*
		 * Create virtual parent directories.
		 */
		while (fn[0] != '\0') {
			struct file *vp;
			struct archive_string as;

			archive_string_init(&as);
			archive_strncat(&as, p, fn - p + l);
			if (as.s[as.length-1] == '/') {
				as.s[as.length-1] = '\0';
				as.length--;
			}
			vp = file_create_virtual_dir(a, xar, as.s);
			if (vp == NULL) {
				archive_string_free(&as);
				archive_set_error(&a->archive, ENOMEM,
				    "Can't allocate memory");
				file_free(file);
				*filepp = NULL;
				return (ARCHIVE_FATAL);
			}
			archive_string_free(&as);
			if (file_gen_utility_names(a, vp) <= ARCHIVE_FAILED)
				return (ARCHIVE_FATAL);
			file_add_child_tail(dent, vp);
			file_register(xar, vp);
			np = vp;

			fn += l;
			if (fn[0] == '/')
				fn++;
			l = get_path_component(name, sizeof(name), fn);
			if (l < 0) {
				archive_string_free(&as);
				archive_set_error(&a->archive,
				    ARCHIVE_ERRNO_MISC,
				    "A name buffer is too small");
				file_free(file);
				*filepp = NULL;
				return (ARCHIVE_FATAL);
			}
			dent = np;
		}

		/* Found out the parent directory where isoent can be
		 * inserted. */
		xar->cur_dirent = dent;
		archive_string_empty(&(xar->cur_dirstr));
		archive_string_ensure(&(xar->cur_dirstr),
		    archive_strlen(&(dent->parentdir)) +
		    archive_strlen(&(dent->basename)) + 2);
		if (archive_strlen(&(dent->parentdir)) +
		    archive_strlen(&(dent->basename)) == 0)
			xar->cur_dirstr.s[0] = 0;
		else {
			if (archive_strlen(&(dent->parentdir)) > 0) {
				archive_string_copy(&(xar->cur_dirstr),
				    &(dent->parentdir));
				archive_strappend_char(&(xar->cur_dirstr), '/');
			}
			archive_string_concat(&(xar->cur_dirstr),
			    &(dent->basename));
		}

		if (!file_add_child_tail(dent, file)) {
			np = (struct file *)__archive_rb_tree_find_node(
			    &(dent->rbtree), file->basename.s);
			goto same_entry;
		}
		return (ARCHIVE_OK);
	}

same_entry:
	/*
	 * We have already has the entry the filename of which is
	 * the same.
	 */
	if (archive_entry_filetype(np->entry) !=
	    archive_entry_filetype(file->entry)) {
		archive_set_error(&a->archive, ARCHIVE_ERRNO_MISC,
		    "Found duplicate entries `%s' and its file type is "
		    "different",
		    archive_entry_pathname(np->entry));
		file_free(file);
		*filepp = NULL;
		return (ARCHIVE_FAILED);
	}

	/* Swap files. */
	ent = np->entry;
	np->entry = file->entry;
	file->entry = ent;
	np->virtual = 0;

	file_free(file);
	*filepp = np;
	return (ARCHIVE_OK);
}