{
		l = get_path_component(name, sizeof(name), fn);
		if (l == 0) {
			np = NULL;
			break;
		}
		if (l < 0) {
			archive_set_error(&a->archive,
			    ARCHIVE_ERRNO_MISC,
			    "A name buffer is too small");
			_isoent_free(isoent);
			return (ARCHIVE_FATAL);
		}

		np = isoent_find_child(dent, name);
		if (np == NULL || fn[0] == '\0')
			break;

		/* Find next subdirectory. */
		if (!np->dir) {
			/* NOT Directory! */
			archive_set_error(&a->archive,
			    ARCHIVE_ERRNO_MISC,
			    "`%s' is not directory, we cannot insert `%s' ",
			    archive_entry_pathname(np->file->entry),
			    archive_entry_pathname(isoent->file->entry));
			_isoent_free(isoent);
			*isoentpp = NULL;
			return (ARCHIVE_FAILED);
		}
		fn += l;
		if (fn[0] == '/')
			fn++;
		dent = np;
	}