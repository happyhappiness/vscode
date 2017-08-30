			    "Truncated Zip file");

			return ARCHIVE_FATAL;

		}



		sconv = zip->sconv;

		if (sconv == NULL && (zip->entry->zip_flags & ZIP_UTF8_NAME))

