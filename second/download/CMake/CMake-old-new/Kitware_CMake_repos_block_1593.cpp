{
		err = set_conversion_failed_error(a, tar->sconv, "Uname");
		if (err == ARCHIVE_FATAL)
			return (err);
	}