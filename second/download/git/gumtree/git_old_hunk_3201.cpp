	if (size >= 1 && buf[size-1] == '\032')
		stats->nonprintable--;
}

/*
 * The same heuristics as diff.c::mmfile_is_binary()
 */
static int is_binary(unsigned long size, struct text_stat *stats)
{

	if (stats->nul)
		return 1;
	if ((stats->printable >> 7) < stats->nonprintable)
		return 1;
	/*
	 * Other heuristics? Average line length might be relevant,
	 * as might LF vs CR vs CRLF counts..
	 *
	 * NOTE! It might be normal to have a low ratio of CRLF to LF
	 * (somebody starts with a LF-only file and edits it with an editor
	 * that adds CRLF only to lines that are added..). But do  we
	 * want to support CR-only? Probably not.
	 */
	return 0;
}

static enum eol output_eol(enum crlf_action crlf_action)
{
	switch (crlf_action) {
	case CRLF_BINARY:
		return EOL_UNSET;
	case CRLF_CRLF:
		return EOL_CRLF;
	case CRLF_INPUT:
		return EOL_LF;
	case CRLF_GUESS:
		if (!auto_crlf)
			return EOL_UNSET;
		/* fall through */
	case CRLF_TEXT:
	case CRLF_AUTO:
		if (auto_crlf == AUTO_CRLF_TRUE)
			return EOL_CRLF;
		else if (auto_crlf == AUTO_CRLF_INPUT)
			return EOL_LF;
		else if (core_eol == EOL_UNSET)
			return EOL_NATIVE;
	}
	return core_eol;
}

static void check_safe_crlf(const char *path, enum crlf_action crlf_action,
                            struct text_stat *stats, enum safe_crlf checksafe)
{
