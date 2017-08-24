{
			/*
			 * Specify UTF-8 character-set to be used for
			 * filenames. This is almost the test that
			 * running platform supports the string conversion.
			 * Especially libarchive_test needs this trick for
			 * its test.
			 */
			pax->sconv_utf8 = archive_string_conversion_to_charset(
			    &(a->archive), "UTF-8", 0);
			if (pax->sconv_utf8 == NULL)
				ret = ARCHIVE_FATAL;
			else
				ret = ARCHIVE_OK;
		}