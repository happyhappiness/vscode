static enum crlf_action git_path_check_crlf(struct git_attr_check *check)
{
	const char *value = check->value;

	if (ATTR_TRUE(value))
		return CRLF_TEXT;
	else if (ATTR_FALSE(value))
		return CRLF_BINARY;
	else if (ATTR_UNSET(value))
		;
	else if (!strcmp(value, "input"))
		return CRLF_TEXT_INPUT;
	else if (!strcmp(value, "auto"))
		return CRLF_AUTO;
	return CRLF_UNDEFINED;
}