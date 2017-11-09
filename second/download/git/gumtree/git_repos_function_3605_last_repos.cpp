int ws_blank_line(const char *line, int len, unsigned ws_rule)
{
	/*
	 * We _might_ want to treat CR differently from other
	 * whitespace characters when ws_rule has WS_CR_AT_EOL, but
	 * for now we just use this stupid definition.
	 */
	while (len-- > 0) {
		if (!isspace(*line))
			return 0;
		line++;
	}
	return 1;
}