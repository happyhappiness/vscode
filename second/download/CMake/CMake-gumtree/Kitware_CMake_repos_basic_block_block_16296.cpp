{
		/*
		 * Create virtual parent directories.
		 */
		while (fn[0] != '\0') {
			struct isoent *vp;
			struct archive_string as;

			archive_string_init(&as);
			archive_strncat(&as, p, fn - p + l);
			if (as.s[as.length-1] == '/') {
				as.s[as.length-1] = '\0';
				as.length--;
			}
			vp = isoent_create_virtual_dir(a, iso9660, as.s);
			if (vp == NULL) {
				archive_string_free(&as);
				archive_set_error(&a->archive, ENOMEM,
				    "Can't allocate memory");
				_isoent_free(isoent);
				*isoentpp = NULL;
				return (ARCHIVE_FATAL);
			}
			archive_string_free(&as);

			if (vp->file->dircnt > iso9660->dircnt_max)
				iso9660->dircnt_max = vp->file->dircnt;
			isoent_add_child_tail(dent, vp);
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
				_isoent_free(isoent);
				*isoentpp = NULL;
				return (ARCHIVE_FATAL);
			}
			dent = np;
		}

		/* Found out the parent directory where isoent can be
		 * inserted. */
		iso9660->cur_dirent = dent;
		archive_string_empty(&(iso9660->cur_dirstr));
		archive_string_ensure(&(iso9660->cur_dirstr),
		    archive_strlen(&(dent->file->parentdir)) +
		    archive_strlen(&(dent->file->basename)) + 2);
		if (archive_strlen(&(dent->file->parentdir)) +
		    archive_strlen(&(dent->file->basename)) == 0)
			iso9660->cur_dirstr.s[0] = 0;
		else {
			if (archive_strlen(&(dent->file->parentdir)) > 0) {
				archive_string_copy(&(iso9660->cur_dirstr),
				    &(dent->file->parentdir));
				archive_strappend_char(&(iso9660->cur_dirstr), '/');
			}
			archive_string_concat(&(iso9660->cur_dirstr),
			    &(dent->file->basename));
		}

		if (!isoent_add_child_tail(dent, isoent)) {
			np = (struct isoent *)__archive_rb_tree_find_node(
			    &(dent->rbtree), isoent->file->basename.s);
			goto same_entry;
		}
		return (ARCHIVE_OK);
	}