void option_error(void)
{
	if (!err_buf[0]) {
		strcpy(err_buf, "Error parsing options: "
		    "option may be supported on client but not on server?\n");
	}

	rprintf(FERROR, RSYNC_NAME ": %s", err_buf);
}