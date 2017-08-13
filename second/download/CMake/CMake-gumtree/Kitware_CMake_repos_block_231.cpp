{
			/* NOT Directory! */
			archive_set_error(&a->archive,
			    ARCHIVE_ERRNO_MISC,
			    "`%s' is not directory, we cannot insert `%s' ",
			    np->pathname.s, file->pathname.s);
			return (ARCHIVE_FAILED);
		}