{
			ustar->opt_sconv = archive_string_conversion_to_charset(
			    &a->archive, val, 0);
			if (ustar->opt_sconv != NULL)
				ret = ARCHIVE_OK;
			else
				ret = ARCHIVE_FATAL;
		}