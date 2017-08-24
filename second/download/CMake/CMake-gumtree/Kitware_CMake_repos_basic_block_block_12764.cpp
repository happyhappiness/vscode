(tar->sconv_acl == NULL) {
		tar->sconv_acl = archive_string_conversion_from_charset(
		    &(a->archive), "UTF-8", 1);
		if (tar->sconv_acl == NULL)
			return (ARCHIVE_FATAL);
	}