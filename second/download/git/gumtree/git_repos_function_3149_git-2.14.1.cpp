static enum eol git_path_check_eol(struct attr_check_item *check)
{
	const char *value = check->value;

	if (ATTR_UNSET(value))
		;
	else if (!strcmp(value, "lf"))
		return EOL_LF;
	else if (!strcmp(value, "crlf"))
		return EOL_CRLF;
	return EOL_UNSET;
}