archive_set_error(&a->archive, ARCHIVE_ERRNO_MISC,
			    "Decryption is unsupported due to lack of "
			    "crypto library")