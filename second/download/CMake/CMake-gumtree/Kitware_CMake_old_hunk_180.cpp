			&a->archive, ARCHIVE_ERRNO_MISC,

			"Bad record header");

		return (ARCHIVE_FATAL);

	} else if ((ver = _warc_rdver(buf, eoh - buf)) > 10000U) {

		/* nawww, I wish they promised backward compatibility

		 * anyhoo, in their infinite wisdom the 28500 guys might

		 * come up with something we can't possibly handle so

		 * best end things here */

		archive_set_error(

			&a->archive, ARCHIVE_ERRNO_MISC,

			"Unsupported record version");

		return (ARCHIVE_FATAL);

	} else if ((cntlen = _warc_rdlen(buf, eoh - buf)) < 0) {

		/* nightmare!  the specs say content-length is mandatory

		 * so I don't feel overly bad stopping the reader here */

		archive_set_error(

			&a->archive, EINVAL,

			"Bad content length");

		return (ARCHIVE_FATAL);

	} else if ((rtime = _warc_rdrtm(buf, eoh - buf)) == (time_t)-1) {

		/* record time is mandatory as per WARC/1.0,

		 * so just barf here, fast and loud */

		archive_set_error(

