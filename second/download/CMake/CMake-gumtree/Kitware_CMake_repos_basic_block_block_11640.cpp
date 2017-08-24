(build_pathname_utf16be(iso9660->utf16be_path,
		    UTF16_NAME_MAX, &(iso9660->utf16be_path_len), file) != 0) {
			archive_set_error(&a->archive,
			    ARCHIVE_ERRNO_FILE_FORMAT,
			    "Pathname is too long");
			return (ARCHIVE_FATAL);
		}