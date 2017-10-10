		count++;
	if (options->output_format & DIFF_FORMAT_CHECKDIFF)
		count++;
	if (options->output_format & DIFF_FORMAT_NO_OUTPUT)
		count++;
	if (count > 1)
		die("--name-only, --name-status, --check and -s are mutually exclusive");

	/*
	 * Most of the time we can say "there are changes"
	 * only by checking if there are changed paths, but
	 * --ignore-whitespace* options force us to look
	 * inside contents.
