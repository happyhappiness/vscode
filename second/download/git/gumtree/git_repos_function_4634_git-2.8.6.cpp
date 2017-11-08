static void check_whitespace(const char *line, int len, unsigned ws_rule)
{
	unsigned result = ws_check(line + 1, len - 1, ws_rule);

	record_ws_error(result, line + 1, len - 2, linenr);
}