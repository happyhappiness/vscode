{
		int err = 0;
		if (avail < 16) {
			archive_set_error(&a->archive,
			    ARCHIVE_ERRNO_FILE_FORMAT,
			    "Illegal zisofs file body");
			return (ARCHIVE_FATAL);
		}

		if (memcmp(p, zisofs_magic, sizeof(zisofs_magic)) != 0)
			err = 1;
		else if (archive_le32dec(p + 8) != zisofs->pz_uncompressed_size)
			err = 1;
		else if (p[12] != 4 || p[13] != zisofs->pz_log2_bs)
			err = 1;
		if (err) {
			archive_set_error(&a->archive,
			    ARCHIVE_ERRNO_FILE_FORMAT,
			    "Illegal zisofs file body");
			return (ARCHIVE_FATAL);
		}
		avail -= 16;
		p += 16;
		zisofs->header_passed = 1;
	}