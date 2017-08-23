{
		/* still no good, the header end might be beyond the
		 * probe we've requested, but then again who'd cram
		 * so much stuff into the header *and* be 28500-compliant */
		archive_set_error(
			&a->archive, ARCHIVE_ERRNO_MISC,
			"Bad record header");
		return (ARCHIVE_FATAL);
	}