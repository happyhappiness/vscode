unsigned parse_whitespace_rule(const char *string)
{
	unsigned rule = WS_DEFAULT_RULE;

	while (string) {
		int i;
		size_t len;
		const char *ep;
		int negated = 0;

		string = string + strspn(string, ", \t\n\r");
		ep = strchrnul(string, ',');
		len = ep - string;

		if (*string == '-') {
			negated = 1;
			string++;
			len--;
		}
		if (!len)
			break;
		for (i = 0; i < ARRAY_SIZE(whitespace_rule_names); i++) {
			if (strncmp(whitespace_rule_names[i].rule_name,
				    string, len))
				continue;
			if (negated)
				rule &= ~whitespace_rule_names[i].rule_bits;
			else
				rule |= whitespace_rule_names[i].rule_bits;
			break;
		}
		if (strncmp(string, "tabwidth=", 9) == 0) {
			unsigned tabwidth = atoi(string + 9);
			if (0 < tabwidth && tabwidth < 0100) {
				rule &= ~WS_TAB_WIDTH_MASK;
				rule |= tabwidth;
			}
			else
				warning("tabwidth %.*s out of range",
					(int)(len - 9), string + 9);
		}
		string = ep;
	}

	if (rule & WS_TAB_IN_INDENT && rule & WS_INDENT_WITH_NON_TAB)
		die("cannot enforce both tab-in-indent and indent-with-non-tab");
	return rule;
}