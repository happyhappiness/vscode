{
			r = get_entry_symlink(a, entry_main, &linkpath,
			    &linkpath_length, NULL);
			if (r == ARCHIVE_FATAL)
				return (r);
			archive_set_error(&a->archive,
			    ARCHIVE_ERRNO_FILE_FORMAT,
			    "Can't translate linkname '%s' to %s", linkpath,
			    archive_string_conversion_charset_name(sconv));
			ret = ARCHIVE_WARN;
			sconv = NULL;
		}