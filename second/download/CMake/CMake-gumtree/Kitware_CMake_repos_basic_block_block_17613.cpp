(strcmp(val, "aes256") == 0) {
			if (is_winzip_aes_encryption_supported(
			    ENCRYPTION_WINZIP_AES256)) {
				zip->encryption_type = ENCRYPTION_WINZIP_AES256;
				ret = ARCHIVE_OK;
			} else {
				archive_set_error(&a->archive,
				    ARCHIVE_ERRNO_MISC,
				    "encryption not supported");
			}
		}