(archive_string_append_from_wcs(&fn, wfilename,
		    wcslen(wfilename)) != 0) {
			archive_set_error(a, EINVAL,
			    "Failed to convert a wide-character filename to"
			    " a multi-byte filename");
			archive_string_free(&fn);
			return (ARCHIVE_FATAL);
		}