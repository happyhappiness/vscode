{
		sconv = archive_string_conversion_from_charset(
		    &(a->archive), "UTF-8", 1);
		if (sconv == NULL)
			return (ARCHIVE_FATAL);
		if (tar->compat_2x)
			archive_string_conversion_set_opt(sconv,
			    SCONV_SET_OPT_UTF8_LIBARCHIVE2X);
	}