static int text_eol_is_crlf(void)
{
	if (auto_crlf == AUTO_CRLF_TRUE)
		return 1;
	else if (auto_crlf == AUTO_CRLF_INPUT)
		return 0;
	if (core_eol == EOL_CRLF)
		return 1;
	if (core_eol == EOL_UNSET && EOL_NATIVE == EOL_CRLF)
		return 1;
	return 0;
}