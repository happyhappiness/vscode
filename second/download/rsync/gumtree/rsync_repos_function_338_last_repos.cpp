void log_delete(const char *fname, int mode)
{
	static struct {
		union file_extras ex[4]; /* just in case... */
		struct file_struct file;
	} x; /* Zero-initialized due to static declaration. */
	int len = strlen(fname);
	const char *fmt;

	x.file.mode = mode;

	if (am_server && protocol_version >= 29 && len < MAXPATHLEN) {
		if (S_ISDIR(mode))
			len++; /* directories include trailing null */
		send_msg(MSG_DELETED, fname, len, am_generator);
	} else if (!INFO_GTE(DEL, 1) && !stdout_format)
		;
	else {
		fmt = stdout_format_has_o_or_i ? stdout_format : "deleting %n";
		log_formatted(FCLIENT, fmt, "del.", &x.file, fname, ITEM_DELETED, NULL);
	}

	if (!logfile_name || dry_run || !logfile_format)
		return;

	fmt = logfile_format_has_o_or_i ? logfile_format : "deleting %n";
	log_formatted(FLOG, fmt, "del.", &x.file, fname, ITEM_DELETED, NULL);
}