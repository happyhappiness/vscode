{
			archive_set_error(&a->archive, ARCHIVE_ERRNO_MISC,
			    "Zip file with oversized link entry");
			return ARCHIVE_FATAL;
		}