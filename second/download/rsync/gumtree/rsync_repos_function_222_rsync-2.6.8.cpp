void log_item(struct file_struct *file, struct stats *initial_stats,
	      int iflags, char *hlink)
{
	char *s_or_r = am_sender ? "send" : "recv";

	if (lp_transfer_logging(module_id)) {
		log_formatted(FLOG, lp_log_format(module_id), s_or_r,
			      file, initial_stats, iflags, hlink);
	} else if (log_format && !am_server) {
		log_formatted(FNAME, log_format, s_or_r,
			      file, initial_stats, iflags, hlink);
	}
}