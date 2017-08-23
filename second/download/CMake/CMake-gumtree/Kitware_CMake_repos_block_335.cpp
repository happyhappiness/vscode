{
			archive_set_error(&a->archive, error_number, "%s",
			    error_string.s);
			free(linkname_copy);
			archive_string_free(&error_string);
			/*
			 * EPERM is more appropriate than error_number for our
			 * callers
			 */
			return (EPERM);
		}