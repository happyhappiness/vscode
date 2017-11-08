void log_delete(char *fname, int mode)
{
	static struct file_struct file;
	int len = strlen(fname);
	char *fmt;

	file.mode = mode;
	file.basename = fname;

	if (!verbose && !log_format)
		;
	else if (am_server && protocol_version >= 29 && len < MAXPATHLEN) {
		if (S_ISDIR(mode))
			len++; /* directories include trailing null */
		send_msg(MSG_DELETED, fname, len);
	} else {
		fmt = log_format_has_o_or_i ? log_format : "deleting %n";
		log_formatted(FCLIENT, fmt, "del.", &file, &stats,
			      ITEM_DELETED, NULL);
	}

	if (!am_daemon || dry_run || !lp_transfer_logging(module_id))
		return;

	fmt = daemon_log_format_has_o_or_i ? lp_log_format(module_id) : "deleting %n";
	log_formatted(FLOG, fmt, "del.", &file, &stats, ITEM_DELETED, NULL);
}