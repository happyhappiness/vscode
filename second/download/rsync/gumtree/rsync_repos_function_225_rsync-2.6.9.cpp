void log_delete(char *fname, int mode)
{
	static struct file_struct file;
	int len = strlen(fname);
	char *fmt;

	file.mode = mode;
	file.basename = fname;

	if (!verbose && !stdout_format)
		;
	else if (am_server && protocol_version >= 29 && len < MAXPATHLEN) {
		if (S_ISDIR(mode))
			len++; /* directories include trailing null */
		send_msg(MSG_DELETED, fname, len);
	} else {
		fmt = stdout_format_has_o_or_i ? stdout_format : "deleting %n";
		log_formatted(FCLIENT, fmt, "del.", &file, &stats,
			      ITEM_DELETED, NULL);
	}

	if (!logfile_name || dry_run || !logfile_format)
		return;

	fmt = logfile_format_has_o_or_i ? logfile_format : "deleting %n";
	log_formatted(FLOG, fmt, "del.", &file, &stats, ITEM_DELETED, NULL);
}