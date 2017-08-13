{
			if (ignore_mod_err)
				continue;
			/* The module name is wrong. */
			archive_set_error(a, ARCHIVE_ERRNO_MISC,
			    "Unknown module name: `%s'", mod);
			free(data);
			return (ARCHIVE_FAILED);
		}