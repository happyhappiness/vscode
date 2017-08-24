{
			tar->opt_sconv =
			    archive_string_conversion_from_charset(
				&a->archive, val, 0);
			if (tar->opt_sconv != NULL)
				ret = ARCHIVE_OK;
			else
				ret = ARCHIVE_FATAL;
		}