{
		/* Create a character conversion object. */
		if (xar->sconv == NULL) {
			xar->sconv = archive_string_conversion_from_charset(
			    &(a->archive), "UTF-8", 1);
			if (xar->sconv == NULL)
				return (ARCHIVE_FATAL);
		}

		/* Read TOC. */
		r = read_toc(a);
		if (r != ARCHIVE_OK)
			return (r);
	}