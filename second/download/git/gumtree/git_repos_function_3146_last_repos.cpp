static int will_convert_lf_to_crlf(size_t len, struct text_stat *stats,
				   enum crlf_action crlf_action)
{
	if (output_eol(crlf_action) != EOL_CRLF)
		return 0;
	/* No "naked" LF? Nothing to convert, regardless. */
	if (!stats->lonelf)
		return 0;

	if (crlf_action == CRLF_AUTO || crlf_action == CRLF_AUTO_INPUT || crlf_action == CRLF_AUTO_CRLF) {
		/* If we have any CR or CRLF line endings, we do not touch it */
		/* This is the new safer autocrlf-handling */
		if (stats->lonecr || stats->crlf)
			return 0;

		if (convert_is_binary(len, stats))
			return 0;
	}
	return 1;

}