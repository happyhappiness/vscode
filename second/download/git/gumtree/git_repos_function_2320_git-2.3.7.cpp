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