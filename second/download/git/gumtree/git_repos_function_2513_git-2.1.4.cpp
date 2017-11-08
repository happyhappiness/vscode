int for_each_reflog_ent_reverse(const char *refname, each_reflog_ent_fn fn, void *cb_data)
{
	struct strbuf sb = STRBUF_INIT;
	FILE *logfp;
	long pos;
	int ret = 0, at_tail = 1;

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
		at_tail = 0;

		while (buf < scanp) {
			/*
			 * terminating LF of the previous line, or the beginning
			 * of the buffer.
			 */
			char *bp;

			bp = find_beginning_of_line(buf, scanp);

			if (*bp != '\n') {
				strbuf_splice(&sb, 0, 0, buf, endp - buf);
				if (pos)
					break; /* need to fill another block */
				scanp = buf - 1; /* leave loop */
			} else {
				/*
				 * (bp + 1) thru endp is the beginning of the
				 * current line we have in sb
				 */
				strbuf_splice(&sb, 0, 0, bp + 1, endp - (bp + 1));
				scanp = bp;
				endp = bp + 1;
			}
			ret = show_one_reflog_ent(&sb, fn, cb_data);
			strbuf_reset(&sb);
			if (ret)
				break;
		}

	}
	if (!ret && sb.len)
		ret = show_one_reflog_ent(&sb, fn, cb_data);

	fclose(logfp);
	strbuf_release(&sb);
	return ret;
}