void log_item(enum logcode code, struct file_struct *file, int iflags, const char *hlink)
{
	const char *s_or_r = am_sender ? "send" : "recv";

	if (code != FLOG && stdout_format && !am_server)
		log_formatted(FCLIENT, stdout_format, s_or_r, file, NULL, iflags, hlink);
	if (code != FCLIENT && logfile_format && *logfile_format)
		log_formatted(FLOG, logfile_format, s_or_r, file, NULL, iflags, hlink);
}