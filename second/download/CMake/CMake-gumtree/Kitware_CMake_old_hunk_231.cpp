		else

			archive_set_error(a, errno, "Can't stat '%s'",

			    filename);

		return (ARCHIVE_FATAL);

	}



	/*

