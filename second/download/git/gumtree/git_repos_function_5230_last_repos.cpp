void shortlog_init(struct shortlog *log)
{
	memset(log, 0, sizeof(*log));

	read_mailmap(&log->mailmap, &log->common_repo_prefix);

	log->list.strdup_strings = 1;
	log->wrap = DEFAULT_WRAPLEN;
	log->in1 = DEFAULT_INDENT1;
	log->in2 = DEFAULT_INDENT2;
}