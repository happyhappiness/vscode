(np == NULL) {
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