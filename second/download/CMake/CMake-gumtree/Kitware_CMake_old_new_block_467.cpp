{
		zip->has_encrypted_entries = 1;
		archive_set_error(&a->archive, ARCHIVE_ERRNO_FILE_FORMAT,
		    "Encrypted file is unsupported");
		return (ARCHIVE_FAILED);
	}