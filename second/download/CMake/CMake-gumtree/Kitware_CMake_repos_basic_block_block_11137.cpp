{
		/* Choose the default conversion. */
		if (!cab->init_default_conversion) {
			cab->sconv_default =
			    archive_string_default_conversion_for_read(
			      &(a->archive));
			cab->init_default_conversion = 1;
		}
		sconv = cab->sconv_default;
	}