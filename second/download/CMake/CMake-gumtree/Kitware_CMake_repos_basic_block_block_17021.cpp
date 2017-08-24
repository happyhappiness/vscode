{
		const char *oname;
		char *name, *bname;
		size_t name_length;
		struct archive_entry *extra = archive_entry_new2(&a->archive);

		oname = archive_entry_pathname(entry_original);
		name_length = strlen(oname);
		name = malloc(name_length + 3);
		if (name == NULL || extra == NULL) {
			/* XXX error message */
			archive_entry_free(extra);
			free(name);
			return (ARCHIVE_FAILED);
		}
		strcpy(name, oname);
		/* Find last '/'; strip trailing '/' characters */
		bname = strrchr(name, '/');
		while (bname != NULL && bname[1] == '\0') {
			*bname = '\0';
			bname = strrchr(name, '/');
		}
		if (bname == NULL) {
			memmove(name + 2, name, name_length + 1);
			memmove(name, "._", 2);
		} else {
			bname += 1;
			memmove(bname + 2, bname, strlen(bname) + 1);
			memmove(bname, "._", 2);
		}
		archive_entry_copy_pathname(extra, name);
		free(name);

		archive_entry_set_size(extra, mac_metadata_size);
		archive_entry_set_filetype(extra, AE_IFREG);
		archive_entry_set_perm(extra,
		    archive_entry_perm(entry_original));
		archive_entry_set_mtime(extra,
		    archive_entry_mtime(entry_original),
		    archive_entry_mtime_nsec(entry_original));
		archive_entry_set_gid(extra,
		    archive_entry_gid(entry_original));
		archive_entry_set_gname(extra,
		    archive_entry_gname(entry_original));
		archive_entry_set_uid(extra,
		    archive_entry_uid(entry_original));
		archive_entry_set_uname(extra,
		    archive_entry_uname(entry_original));

		/* Recurse to write the special copyfile entry. */
		r = archive_write_pax_header(a, extra);
		archive_entry_free(extra);
		if (r < ARCHIVE_WARN)
			return (r);
		if (r < ret)
			ret = r;
		r = (int)archive_write_pax_data(a, mac_metadata,
		    mac_metadata_size);
		if (r < ARCHIVE_WARN)
			return (r);
		if (r < ret)
			ret = r;
		r = archive_write_pax_finish_entry(a);
		if (r < ARCHIVE_WARN)
			return (r);
		if (r < ret)
			ret = r;
	}