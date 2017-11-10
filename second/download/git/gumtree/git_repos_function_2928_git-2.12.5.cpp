static int crlf_to_git(const char *path, const char *src, size_t len,
		       struct strbuf *buf,
		       enum crlf_action crlf_action, enum safe_crlf checksafe)
{
	struct text_stat stats;
	char *dst;
	int convert_crlf_into_lf;

	if (crlf_action == CRLF_BINARY ||
	    (src && !len))
		return 0;

	/*
	 * If we are doing a dry-run and have no source buffer, there is
	 * nothing to analyze; we must assume we would convert.
	 */
	if (!buf && !src)
		return 1;

	gather_stats(src, len, &stats);
	/* Optimization: No CRLF? Nothing to convert, regardless. */
	convert_crlf_into_lf = !!stats.crlf;

	if (crlf_action == CRLF_AUTO || crlf_action == CRLF_AUTO_INPUT || crlf_action == CRLF_AUTO_CRLF) {
		if (convert_is_binary(len, &stats))
			return 0;
		/*
		 * If the file in the index has any CR in it, do not
		 * convert.  This is the new safer autocrlf handling,
		 * unless we want to renormalize in a merge or
		 * cherry-pick.
		 */
		if ((checksafe != SAFE_CRLF_RENORMALIZE) && has_cr_in_index(path))
			convert_crlf_into_lf = 0;
	}
	if ((checksafe == SAFE_CRLF_WARN ||
	    (checksafe == SAFE_CRLF_FAIL)) && len) {
		struct text_stat new_stats;
		memcpy(&new_stats, &stats, sizeof(new_stats));
		/* simulate "git add" */
		if (convert_crlf_into_lf) {
			new_stats.lonelf += new_stats.crlf;
			new_stats.crlf = 0;
		}
		/* simulate "git checkout" */
		if (will_convert_lf_to_crlf(len, &new_stats, crlf_action)) {
			new_stats.crlf += new_stats.lonelf;
			new_stats.lonelf = 0;
		}
		check_safe_crlf(path, crlf_action, &stats, &new_stats, checksafe);
	}
	if (!convert_crlf_into_lf)
		return 0;

	/*
	 * At this point all of our source analysis is done, and we are sure we
	 * would convert. If we are in dry-run mode, we can give an answer.
	 */
	if (!buf)
		return 1;

	/* only grow if not in place */
	if (strbuf_avail(buf) + buf->len < len)
		strbuf_grow(buf, len - buf->len);
	dst = buf->buf;
	if (crlf_action == CRLF_AUTO || crlf_action == CRLF_AUTO_INPUT || crlf_action == CRLF_AUTO_CRLF) {
		/*
		 * If we guessed, we already know we rejected a file with
		 * lone CR, and we can strip a CR without looking at what
		 * follow it.
		 */
		do {
			unsigned char c = *src++;
			if (c != '\r')
				*dst++ = c;
		} while (--len);
	} else {
		do {
			unsigned char c = *src++;
			if (! (c == '\r' && (1 < len && *src == '\n')))
				*dst++ = c;
		} while (--len);
	}
	strbuf_setlen(buf, dst - buf->buf);
	return 1;
}