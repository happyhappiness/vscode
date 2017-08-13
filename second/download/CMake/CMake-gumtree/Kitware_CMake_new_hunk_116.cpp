			&a->archive, ARCHIVE_ERRNO_MISC,
			"Bad record header");
		return (ARCHIVE_FATAL);
	}
	ver = _warc_rdver(buf, eoh - buf);
	/* we currently support WARC 0.12 to 1.0 */
	if (ver == 0U) {
		archive_set_error(
			&a->archive, ARCHIVE_ERRNO_MISC,
			"Invalid record version");
		return (ARCHIVE_FATAL);
	} else if (ver < 1200U || ver > 10000U) {
		archive_set_error(
			&a->archive, ARCHIVE_ERRNO_MISC,
			"Unsupported record version: %u.%u",
			ver / 10000, (ver % 10000) / 100);
		return (ARCHIVE_FATAL);
	}
	cntlen = _warc_rdlen(buf, eoh - buf);
	if (cntlen < 0) {
		/* nightmare!  the specs say content-length is mandatory
		 * so I don't feel overly bad stopping the reader here */
		archive_set_error(
			&a->archive, EINVAL,
			"Bad content length");
		return (ARCHIVE_FATAL);
	}
	rtime = _warc_rdrtm(buf, eoh - buf);
	if (rtime == (time_t)-1) {
		/* record time is mandatory as per WARC/1.0,
		 * so just barf here, fast and loud */
		archive_set_error(
