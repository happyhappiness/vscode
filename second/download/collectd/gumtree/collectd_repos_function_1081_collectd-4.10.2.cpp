static int tbl_read_table (tbl_t *tbl)
{
	FILE *fh;
	char  buf[4096];

	fh = fopen (tbl->file, "r");
	if (NULL == fh) {
		char errbuf[1024];
		log_err ("Failed to open file \"%s\": %s.", tbl->file,
				sstrerror (errno, errbuf, sizeof (errbuf)));
		return -1;
	}

	buf[sizeof (buf) - 1] = '\0';
	while (NULL != fgets (buf, sizeof (buf), fh)) {
		if ('\0' != buf[sizeof (buf) - 1]) {
			buf[sizeof (buf) - 1] = '\0';
			log_err ("Table %s: Truncated line: %s", tbl->file, buf);
		}

		if (0 != tbl_parse_line (tbl, buf, sizeof (buf))) {
			log_err ("Table %s: Failed to parse line: %s", tbl->file, buf);
			continue;
		}
	}

	if (0 != ferror (fh)) {
		char errbuf[1024];
		log_err ("Failed to read from file \"%s\": %s.", tbl->file,
				sstrerror (errno, errbuf, sizeof (errbuf)));
		fclose (fh);
		return -1;
	}

	fclose (fh);
	return 0;
}