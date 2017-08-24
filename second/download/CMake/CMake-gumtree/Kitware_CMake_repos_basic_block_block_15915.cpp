(iso9660->opt.joliet) {
		/* Make a new tree for joliet. */
		ret = isoent_clone_tree(a, &(iso9660->joliet.rootent),
		    iso9660->primary.rootent);
		if (ret < 0)
			return (ret);
		/* Make sure we have UTF-16BE converters.
		 * if there is no file entry, converters are still
		 * uninitialized. */
		if (iso9660->sconv_to_utf16be == NULL) {
			iso9660->sconv_to_utf16be =
			    archive_string_conversion_to_charset(
				&(a->archive), "UTF-16BE", 1);
			if (iso9660->sconv_to_utf16be == NULL)
				/* Couldn't allocate memory */
				return (ARCHIVE_FATAL);
			iso9660->sconv_from_utf16be =
			    archive_string_conversion_from_charset(
				&(a->archive), "UTF-16BE", 1);
			if (iso9660->sconv_from_utf16be == NULL)
				/* Couldn't allocate memory */
				return (ARCHIVE_FATAL);
		}
	}