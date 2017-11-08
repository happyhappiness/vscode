static enum crlf_action input_crlf_action(enum crlf_action text_attr, enum eol eol_attr)
{
	if (text_attr == CRLF_BINARY)
		return CRLF_BINARY;
	if (eol_attr == EOL_LF)
		return CRLF_INPUT;
	if (eol_attr == EOL_CRLF)
		return CRLF_CRLF;
	return text_attr;
}