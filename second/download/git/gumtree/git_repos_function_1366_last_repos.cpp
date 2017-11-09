static void check_old_for_crlf(struct patch *patch, const char *line, int len)
{
	if (len >= 2 && line[len-1] == '\n' && line[len-2] == '\r') {
		patch->ws_rule |= WS_CR_AT_EOL;
		patch->crlf_in_old = 1;
	}
}