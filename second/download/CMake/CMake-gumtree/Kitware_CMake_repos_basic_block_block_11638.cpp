{
		/*
		 * Convert UTF-16BE of a filename to local locale MBS
		 * and store the result into a filename field.
		 */
		if (iso9660->sconv_utf16be == NULL) {
			iso9660->sconv_utf16be =
			    archive_string_conversion_from_charset(
				&(a->archive), "UTF-16BE", 1);
			if (iso9660->sconv_utf16be == NULL)
				/* Couldn't allocate memory */
				return (ARCHIVE_FATAL);
		}
		if (iso9660->utf16be_path == NULL) {
			iso9660->utf16be_path = malloc(UTF16_NAME_MAX);
			if (iso9660->utf16be_path == NULL) {
				archive_set_error(&a->archive, ENOMEM,
				    "No memory");
				return (ARCHIVE_FATAL);
			}
		}
		if (iso9660->utf16be_previous_path == NULL) {
			iso9660->utf16be_previous_path = malloc(UTF16_NAME_MAX);
			if (iso9660->utf16be_previous_path == NULL) {
				archive_set_error(&a->archive, ENOMEM,
				    "No memory");
				return (ARCHIVE_FATAL);
			}
		}

		iso9660->utf16be_path_len = 0;
		if (build_pathname_utf16be(iso9660->utf16be_path,
		    UTF16_NAME_MAX, &(iso9660->utf16be_path_len), file) != 0) {
			archive_set_error(&a->archive,
			    ARCHIVE_ERRNO_FILE_FORMAT,
			    "Pathname is too long");
			return (ARCHIVE_FATAL);
		}

		r = archive_entry_copy_pathname_l(entry,
		    (const char *)iso9660->utf16be_path,
		    iso9660->utf16be_path_len,
		    iso9660->sconv_utf16be);
		if (r != 0) {
			if (errno == ENOMEM) {
				archive_set_error(&a->archive, ENOMEM,
				    "No memory for Pathname");
				return (ARCHIVE_FATAL);
			}
			archive_set_error(&a->archive,
			    ARCHIVE_ERRNO_FILE_FORMAT,
			    "Pathname cannot be converted "
			    "from %s to current locale.",
			    archive_string_conversion_charset_name(
			      iso9660->sconv_utf16be));

			rd_r = ARCHIVE_WARN;
		}
	}