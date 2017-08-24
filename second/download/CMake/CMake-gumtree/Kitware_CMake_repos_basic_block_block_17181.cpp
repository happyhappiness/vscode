(!ustar->init_default_conversion) {
			ustar->sconv_default =
			    archive_string_default_conversion_for_write(&(a->archive));
			ustar->init_default_conversion = 1;
		}