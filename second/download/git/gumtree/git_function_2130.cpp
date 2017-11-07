static enum eol output_eol(enum crlf_action crlf_action)
{
	switch (crlf_action) {
	case CRLF_BINARY:
		return EOL_UNSET;
	case CRLF_TEXT_CRLF:
		return EOL_CRLF;
	case CRLF_TEXT_INPUT:
		return EOL_LF;
	case CRLF_UNDEFINED:
	case CRLF_AUTO_CRLF:
	case CRLF_AUTO_INPUT:
	case CRLF_TEXT:
	case CRLF_AUTO:
		/* fall through */
		return text_eol_is_crlf() ? EOL_CRLF : EOL_LF;
	}
	warning("Illegal crlf_action %d\n", (int)crlf_action);
	return core_eol;
}