void log_item(enum logcode code, struct file_struct *file,
	      struct stats *initial_stats, int iflags, char *hlink)
{
	char *s_or_r = am_sender ? "send" : "recv";

	if (code != FLOG && stdout_format && !am_server) {
		log_formatted(FCLIENT, stdout_format, s_or_r,
			      file, initial_stats, iflags, hlink);
	}
	if (code != FCLIENT && logfile_format && *logfile_format) {
		log_formatted(FLOG, logfile_format, s_or_r,
			      file, initial_stats, iflags, hlink);
	}
}