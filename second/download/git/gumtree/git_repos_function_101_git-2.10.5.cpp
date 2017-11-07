const char *logmsg_reencode(const struct commit *commit,
			    char **commit_encoding,
			    const char *output_encoding)
{
	static const char *utf8 = "UTF-8";
	const char *use_encoding;
	char *encoding;
	const char *msg = get_commit_buffer(commit, NULL);
	char *out;

	if (!output_encoding || !*output_encoding) {
		if (commit_encoding)
			*commit_encoding = get_header(msg, "encoding");
		return msg;
	}
	encoding = get_header(msg, "encoding");
	if (commit_encoding)
		*commit_encoding = encoding;
	use_encoding = encoding ? encoding : utf8;
	if (same_encoding(use_encoding, output_encoding)) {
		/*
		 * No encoding work to be done. If we have no encoding header
		 * at all, then there's nothing to do, and we can return the
		 * message verbatim (whether newly allocated or not).
		 */
		if (!encoding)
			return msg;

		/*
		 * Otherwise, we still want to munge the encoding header in the
		 * result, which will be done by modifying the buffer. If we
		 * are using a fresh copy, we can reuse it. But if we are using
		 * the cached copy from get_commit_buffer, we need to duplicate it
		 * to avoid munging the cached copy.
		 */
		if (msg == get_cached_commit_buffer(commit, NULL))
			out = xstrdup(msg);
		else
			out = (char *)msg;
	}
	else {
		/*
		 * There's actual encoding work to do. Do the reencoding, which
		 * still leaves the header to be replaced in the next step. At
		 * this point, we are done with msg. If we allocated a fresh
		 * copy, we can free it.
		 */
		out = reencode_string(msg, output_encoding, use_encoding);
		if (out)
			unuse_commit_buffer(commit, msg);
	}

	/*
	 * This replacement actually consumes the buffer we hand it, so we do
	 * not have to worry about freeing the old "out" here.
	 */
	if (out)
		out = replace_encoding_header(out, output_encoding);

	if (!commit_encoding)
		free(encoding);
	/*
	 * If the re-encoding failed, out might be NULL here; in that
	 * case we just return the commit message verbatim.
	 */
	return out ? out : msg;
}