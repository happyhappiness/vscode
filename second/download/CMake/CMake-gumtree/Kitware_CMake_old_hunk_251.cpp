	/* Get a real compressed file size. */

	lha->compsize -= extdsize - 2;



	if (sum_calculated != headersum) {

		archive_set_error(&a->archive, ARCHIVE_ERRNO_MISC,

		    "LHa header sum error");

