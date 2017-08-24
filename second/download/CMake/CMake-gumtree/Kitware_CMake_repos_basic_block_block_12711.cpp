{
		if (!tar->init_default_conversion) {
			tar->sconv_default =
			    archive_string_default_conversion_for_read(&(a->archive));
			tar->init_default_conversion = 1;
		}
		tar->sconv = tar->sconv_default;
	}