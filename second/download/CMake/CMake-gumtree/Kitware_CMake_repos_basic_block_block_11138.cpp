{
		if (cab->sconv_utf8 == NULL) {
			cab->sconv_utf8 =
			    archive_string_conversion_from_charset(
				&(a->archive), "UTF-8", 1);
			if (cab->sconv_utf8 == NULL)
				return (ARCHIVE_FATAL);
		}
		sconv = cab->sconv_utf8;
	}