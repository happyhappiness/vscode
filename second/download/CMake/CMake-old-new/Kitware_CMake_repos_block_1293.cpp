{
				if (errno == ENOMEM) {
					archive_set_error(&a->archive, ENOMEM,
					    "No memory for Linkname");
					return (ARCHIVE_FATAL);
				}
				archive_set_error(&a->archive,
				    ARCHIVE_ERRNO_FILE_FORMAT,
				    "Linkname cannot be converted "
				    "from %s to current locale.",
				    archive_string_conversion_charset_name(
				      iso9660->sconv_utf16be));
				rd_r = ARCHIVE_WARN;
			}