{
			archive_set_error(a, EINVAL,
			    "Failed to convert a wide-character filename to"
			    " a multi-byte filename");
			archive_string_free(&fn);
			return (ARCHIVE_FATAL);
		}