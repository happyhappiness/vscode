void option_error(void)
{
	if (err_buf[0]) {
		rprintf(FLOG, "%s", err_buf);
		rprintf(FERROR, "%s: %s", RSYNC_NAME, err_buf);
	} else {
		rprintf (FERROR, "Error parsing options: "
			 "option may be supported on client but not on server?\n");
		rprintf (FERROR, RSYNC_NAME ": Error parsing options: "
			 "option may be supported on client but not on server?\n");
	}
}