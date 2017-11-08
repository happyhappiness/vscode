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

			if (*bp == '\n') {
				/*
				 * The newline is the end of the previous line,
				 * so we know we have complete line starting
				 * at (bp + 1). Prefix it onto any prior data
				 * we collected for the line and process it.
				 */
				strbuf_splice(&sb, 0, 0, bp + 1, endp - (bp + 1));
				scanp = bp;
				endp = bp + 1;
				ret = show_one_reflog_ent(&sb, fn, cb_data);
				strbuf_reset(&sb);
				if (ret)
					break;
			} else if (!pos) {
				/*
				 * We are at the start of the buffer, and the
				 * start of the file; there is no previous
				 * line, and we have everything for this one.
				 * Process it, and we can end the loop.
				 */
				strbuf_splice(&sb, 0, 0, buf, endp - buf);
				ret = show_one_reflog_ent(&sb, fn, cb_data);
				strbuf_reset(&sb);
				break;
			}

			if (bp == buf) {
				/*
				 * We are at the start of the buffer, and there
				 * is more file to read backwards. Which means
				 * we are in the middle of a line. Note that we
				 * may get here even if *bp was a newline; that
				 * just means we are at the exact end of the
				 * previous line, rather than some spot in the
				 * middle.
				 *
				 * Save away what we have to be combined with
				 * the data from the next read.
				 */
				strbuf_splice(&sb, 0, 0, buf, endp - buf);
				break;
			}
		}

	}
	if (!ret && sb.len)
		die("BUG: reverse reflog parser had leftover data");

	fclose(logfp);
	strbuf_release(&sb);
	return ret;
}