{
		/* record time is mandatory as per WARC/1.0,
		 * so just barf here, fast and loud */
		archive_set_error(
			&a->archive, EINVAL,
			"Bad record time");
		return (ARCHIVE_FATAL);
	}