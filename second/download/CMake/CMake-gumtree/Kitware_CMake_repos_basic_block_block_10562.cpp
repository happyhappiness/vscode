{
		zip->sconv = archive_string_conversion_from_charset(
		    &a->archive, "UTF-16LE", 1);
		if (zip->sconv == NULL)
			return (ARCHIVE_FATAL);
	}