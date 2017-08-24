(val[0] == '1' || strcmp(val, "traditional") == 0
		    || strcmp(val, "zipcrypt") == 0
		    || strcmp(val, "ZipCrypt") == 0) {
			if (is_traditional_pkware_encryption_supported()) {
				zip->encryption_type = ENCRYPTION_TRADITIONAL;
				ret = ARCHIVE_OK;
			} else {
				archive_set_error(&a->archive,
				    ARCHIVE_ERRNO_MISC,
				    "encryption not supported");
			}
		}