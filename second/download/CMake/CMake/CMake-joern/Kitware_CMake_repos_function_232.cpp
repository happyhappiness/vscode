static int
mtree_entry_tree_add(struct archive_write *a, struct mtree_entry **filep)
{
#if defined(_WIN32) && !defined(__CYGWIN__)
	char name[_MAX_FNAME];/* Included null terminator size. */
#elif defined(NAME_MAX) && NAME_MAX >= 255
	char name[NAME_MAX+1];
#else
	char name[256];
#endif
	struct mtree_writer *mtree = (struct mtree_writer *)a->format_data;
	struct mtree_entry *dent, *file, *np;
	const char *fn, *p;
	int l, r;

	file = *filep;
	if (file->parentdir.length == 0 && file->basename.length == 1 &&
	    file->basename.s[0] == '.') {
		file->parent = file;
		if (mtree->root != NULL) {
			np = mtree->root;
			goto same_entry;
		}
		mtree->root = file;
		mtree_entry_register_add(mtree, file);
		return (ARCHIVE_OK);
	}

	if (file->parentdir.length == 0) {
		archive_set_error(&a->archive, ARCHIVE_ERRNO_MISC,
		    "Internal programing error "
		    "in generating canonical name for %s",
		    file->pathname.s);
		return (ARCHIVE_FAILED);
	}

	fn = p = file->parentdir.s;

	/*
	 * If the path of the parent directory of `file' entry is
	 * the same as the path of `cur_dirent', add `file' entry to
	 * `cur_dirent'.
	 */
	if (archive_strlen(&(mtree->cur_dirstr))
	      == archive_strlen(&(file->parentdir)) &&
	    strcmp(mtree->cur_dirstr.s, fn) == 0) {
		if (!__archive_rb_tree_insert_node(
		    &(mtree->cur_dirent->dir_info->rbtree),
		    (struct archive_rb_node *)file)) {
			/* There is the same name in the tree. */
			np = (struct mtree_entry *)__archive_rb_tree_find_node(
			    &(mtree->cur_dirent->dir_info->rbtree),
			    file->basename.s);
			goto same_entry;
		}
		file->parent = mtree->cur_dirent;
		mtree_entry_register_add(mtree, file);
		return (ARCHIVE_OK);
	}

	dent = mtree->root;
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
			return (ARCHIVE_FATAL);
		}
		if (l == 1 && name[0] == '.' && dent != NULL &&
		    dent == mtree->root) {
			fn += l;
			if (fn[0] == '/')
				fn++;
			continue;
		}

		np = mtree_entry_find_child(dent, name);
		if (np == NULL || fn[0] == '\0')
			break;

		/* Find next sub directory. */
		if (!np->dir_info) {
			/* NOT Directory! */
			archive_set_error(&a->archive,
			    ARCHIVE_ERRNO_MISC,
			    "`%s' is not directory, we cannot insert `%s' ",
			    np->pathname.s, file->pathname.s);
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
			struct mtree_entry *vp;
			struct archive_string as;

			archive_string_init(&as);
			archive_strncat(&as, p, fn - p + l);
			if (as.s[as.length-1] == '/') {
				as.s[as.length-1] = '\0';
				as.length--;
			}
			r = mtree_entry_create_virtual_dir(a, as.s, &vp);
			archive_string_free(&as);
			if (r < ARCHIVE_WARN)
				return (r);

			if (strcmp(vp->pathname.s, ".") == 0) {
				vp->parent = vp;
				mtree->root = vp;
			} else {
				__archive_rb_tree_insert_node(
				    &(dent->dir_info->rbtree),
				    (struct archive_rb_node *)vp);
				vp->parent = dent;
			}
			mtree_entry_register_add(mtree, vp);
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
				return (ARCHIVE_FATAL);
			}
			dent = np;
		}

		/* Found out the parent directory where `file' can be
		 * inserted. */
		mtree->cur_dirent = dent;
		archive_string_empty(&(mtree->cur_dirstr));
		archive_string_ensure(&(mtree->cur_dirstr),
		    archive_strlen(&(dent->parentdir)) +
		    archive_strlen(&(dent->basename)) + 2);
		if (archive_strlen(&(dent->parentdir)) +
		    archive_strlen(&(dent->basename)) == 0)
			mtree->cur_dirstr.s[0] = 0;
		else {
			if (archive_strlen(&(dent->parentdir)) > 0) {
				archive_string_copy(&(mtree->cur_dirstr),
				    &(dent->parentdir));
				archive_strappend_char(
				    &(mtree->cur_dirstr), '/');
			}
			archive_string_concat(&(mtree->cur_dirstr),
			    &(dent->basename));
		}

		if (!__archive_rb_tree_insert_node(
		    &(dent->dir_info->rbtree),
		    (struct archive_rb_node *)file)) {
			np = (struct mtree_entry *)__archive_rb_tree_find_node(
			    &(dent->dir_info->rbtree), file->basename.s);
			goto same_entry;
		}
		file->parent = dent;
		mtree_entry_register_add(mtree, file);
		return (ARCHIVE_OK);
	}

same_entry:
	/*
	 * We have already has the entry the filename of which is
	 * the same.
	 */
	r = mtree_entry_exchange_same_entry(a, np, file);
	if (r < ARCHIVE_WARN)
		return (r);
	if (np->dir_info)
		np->dir_info->virtual = 0;
	*filep = np;
	mtree_entry_free(file);
	return (ARCHIVE_WARN);
}