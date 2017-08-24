(memcmp(header->magic, "ustar", 5) == 0) {
			if (a->archive.archive_format != ARCHIVE_FORMAT_TAR_PAX_INTERCHANGE) {
				a->archive.archive_format = ARCHIVE_FORMAT_TAR_USTAR;
				a->archive.archive_format_name = "POSIX ustar format";
			}
			err = header_ustar(a, tar, entry, h);
		}