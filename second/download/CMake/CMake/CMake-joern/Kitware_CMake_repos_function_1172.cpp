static int
archive_write_shar_header(struct archive_write *a, struct archive_entry *entry)
{
	const char *linkname;
	const char *name;
	char *p, *pp;
	struct shar *shar;

	shar = (struct shar *)a->format_data;
	if (!shar->wrote_header) {
		archive_strcat(&shar->work, "#!/bin/sh\n");
		archive_strcat(&shar->work, "# This is a shell archive\n");
		shar->wrote_header = 1;
	}

	/* Save the entry for the closing. */
	if (shar->entry)
		archive_entry_free(shar->entry);
	shar->entry = archive_entry_clone(entry);
	name = archive_entry_pathname(entry);

	/* Handle some preparatory issues. */
	switch(archive_entry_filetype(entry)) {
	case AE_IFREG:
		/* Only regular files have non-zero size. */
		break;
	case AE_IFDIR:
		archive_entry_set_size(entry, 0);
		/* Don't bother trying to recreate '.' */
		if (strcmp(name, ".") == 0  ||  strcmp(name, "./") == 0)
			return (ARCHIVE_OK);
		break;
	case AE_IFIFO:
	case AE_IFCHR:
	case AE_IFBLK:
		/* All other file types have zero size in the archive. */
		archive_entry_set_size(entry, 0);
		break;
	default:
		archive_entry_set_size(entry, 0);
		if (archive_entry_hardlink(entry) == NULL &&
		    archive_entry_symlink(entry) == NULL) {
			archive_set_error(&a->archive, ARCHIVE_ERRNO_MISC,
			    "shar format cannot archive this");
			return (ARCHIVE_WARN);
		}
	}

	archive_string_empty(&shar->quoted_name);
	shar_quote(&shar->quoted_name, name, 1);

	/* Stock preparation for all file types. */
	archive_string_sprintf(&shar->work, "echo x %s\n", shar->quoted_name.s);

	if (archive_entry_filetype(entry) != AE_IFDIR) {
		/* Try to create the dir. */
		p = strdup(name);
		pp = strrchr(p, '/');
		/* If there is a / character, try to create the dir. */
		if (pp != NULL) {
			*pp = '\0';

			/* Try to avoid a lot of redundant mkdir commands. */
			if (strcmp(p, ".") == 0) {
				/* Don't try to "mkdir ." */
				free(p);
			} else if (shar->last_dir == NULL) {
				archive_strcat(&shar->work, "mkdir -p ");
				shar_quote(&shar->work, p, 1);
				archive_strcat(&shar->work,
				    " > /dev/null 2>&1\n");
				shar->last_dir = p;
			} else if (strcmp(p, shar->last_dir) == 0) {
				/* We've already created this exact dir. */
				free(p);
			} else if (strlen(p) < strlen(shar->last_dir) &&
			    strncmp(p, shar->last_dir, strlen(p)) == 0) {
				/* We've already created a subdir. */
				free(p);
			} else {
				archive_strcat(&shar->work, "mkdir -p ");
				shar_quote(&shar->work, p, 1);
				archive_strcat(&shar->work,
				    " > /dev/null 2>&1\n");
				shar->last_dir = p;
			}
		} else {
			free(p);
		}
	}

	/* Handle file-type specific issues. */
	shar->has_data = 0;
	if ((linkname = archive_entry_hardlink(entry)) != NULL) {
		archive_strcat(&shar->work, "ln -f ");
		shar_quote(&shar->work, linkname, 1);
		archive_string_sprintf(&shar->work, " %s\n",
		    shar->quoted_name.s);
	} else if ((linkname = archive_entry_symlink(entry)) != NULL) {
		archive_strcat(&shar->work, "ln -fs ");
		shar_quote(&shar->work, linkname, 1);
		archive_string_sprintf(&shar->work, " %s\n",
		    shar->quoted_name.s);
	} else {
		switch(archive_entry_filetype(entry)) {
		case AE_IFREG:
			if (archive_entry_size(entry) == 0) {
				/* More portable than "touch." */
				archive_string_sprintf(&shar->work,
				    "test -e \"%s\" || :> \"%s\"\n",
				    shar->quoted_name.s, shar->quoted_name.s);
			} else {
				if (shar->dump) {
					unsigned int mode = archive_entry_mode(entry) & 0777;
					archive_string_sprintf(&shar->work,
					    "uudecode -p > %s << 'SHAR_END'\n",
					    shar->quoted_name.s);
					archive_string_sprintf(&shar->work,
					    "begin %o ", mode);
					shar_quote(&shar->work, name, 0);
					archive_strcat(&shar->work, "\n");
				} else {
					archive_string_sprintf(&shar->work,
					    "sed 's/^X//' > %s << 'SHAR_END'\n",
					    shar->quoted_name.s);
				}
				shar->has_data = 1;
				shar->end_of_line = 1;
				shar->outpos = 0;
			}
			break;
		case AE_IFDIR:
			archive_string_sprintf(&shar->work,
			    "mkdir -p %s > /dev/null 2>&1\n",
			    shar->quoted_name.s);
			/* Record that we just created this directory. */
			if (shar->last_dir != NULL)
				free(shar->last_dir);

			shar->last_dir = strdup(name);
			/* Trim a trailing '/'. */
			pp = strrchr(shar->last_dir, '/');
			if (pp != NULL && pp[1] == '\0')
				*pp = '\0';
			/*
			 * TODO: Put dir name/mode on a list to be fixed
			 * up at end of archive.
			 */
			break;
		case AE_IFIFO:
			archive_string_sprintf(&shar->work,
			    "mkfifo %s\n", shar->quoted_name.s);
			break;
		case AE_IFCHR:
			archive_string_sprintf(&shar->work,
			    "mknod %s c %ju %ju\n", shar->quoted_name.s,
			    (uintmax_t)archive_entry_rdevmajor(entry),
			    (uintmax_t)archive_entry_rdevminor(entry));
			break;
		case AE_IFBLK:
			archive_string_sprintf(&shar->work,
			    "mknod %s b %ju %ju\n", shar->quoted_name.s,
			    (uintmax_t)archive_entry_rdevmajor(entry),
			    (uintmax_t)archive_entry_rdevminor(entry));
			break;
		default:
			return (ARCHIVE_WARN);
		}
	}

	return (ARCHIVE_OK);
}