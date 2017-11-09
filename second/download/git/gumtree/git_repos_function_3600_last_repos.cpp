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
				    !whitespace_rule_names[i].exclude_default)
					all_rule |= whitespace_rule_names[i].rule_bits;
			return all_rule;
		} else if (ATTR_FALSE(value)) {
			/* false (-whitespace) */
			return ws_tab_width(whitespace_rule_cfg);
		} else if (ATTR_UNSET(value)) {
			/* reset to default (!whitespace) */
			return whitespace_rule_cfg;
		} else {
			/* string */
			return parse_whitespace_rule(value);
		}
	} else {
		return whitespace_rule_cfg;
	}
}