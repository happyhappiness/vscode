unsigned ws_check(const char *line, int len, unsigned ws_rule)
{
	return ws_check_emit_1(line, len, ws_rule, NULL, NULL, NULL, NULL);
}