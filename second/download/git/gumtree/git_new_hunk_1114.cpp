
	if (rule & WS_TAB_IN_INDENT && rule & WS_INDENT_WITH_NON_TAB)
		die("cannot enforce both tab-in-indent and indent-with-non-tab");
	return rule;
}

unsigned whitespace_rule(const char *pathname)
{
	static struct attr_check *attr_whitespace_rule;

	if (!attr_whitespace_rule)
		attr_whitespace_rule = attr_check_initl("whitespace", NULL);

	if (!git_check_attr(pathname, attr_whitespace_rule)) {
		const char *value;

		value = attr_whitespace_rule->items[0].value;
		if (ATTR_TRUE(value)) {
			/* true (whitespace) */
			unsigned all_rule = ws_tab_width(whitespace_rule_cfg);
			int i;
			for (i = 0; i < ARRAY_SIZE(whitespace_rule_names); i++)
				if (!whitespace_rule_names[i].loosens_error &&
