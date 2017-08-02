{
			archive_set_error(&a->archive, ERANGE,
			    "Major device number too large");
			ret = ARCHIVE_FAILED;
		}