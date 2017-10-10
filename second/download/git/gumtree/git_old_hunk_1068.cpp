
static int files_for_each_reflog_ent_reverse(struct ref_store *ref_store,
					     const char *refname,
					     each_reflog_ent_fn fn,
					     void *cb_data)
{
	struct strbuf sb = STRBUF_INIT;
	FILE *logfp;
	long pos;
	int ret = 0, at_tail = 1;

	/* Check validity (but we don't need the result): */
	files_downcast(ref_store, 0, "for_each_reflog_ent_reverse");

	logfp = fopen(git_path("logs/%s", refname), "r");
	if (!logfp)
		return -1;

	/* Jump to the end */
	if (fseek(logfp, 0, SEEK_END) < 0)
		return error("cannot seek back reflog for %s: %s",
			     refname, strerror(errno));
	pos = ftell(logfp);
	while (!ret && 0 < pos) {
		int cnt;
		size_t nread;
		char buf[BUFSIZ];
		char *endp, *scanp;

		/* Fill next block from the end */
		cnt = (sizeof(buf) < pos) ? sizeof(buf) : pos;
		if (fseek(logfp, pos - cnt, SEEK_SET))
			return error("cannot seek back reflog for %s: %s",
				     refname, strerror(errno));
		nread = fread(buf, cnt, 1, logfp);
		if (nread != 1)
			return error("cannot read %d bytes from reflog for %s: %s",
				     cnt, refname, strerror(errno));
		pos -= cnt;

		scanp = endp = buf + cnt;
		if (at_tail && scanp[-1] == '\n')
			/* Looking at the final LF at the end of the file */
			scanp--;
