{
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