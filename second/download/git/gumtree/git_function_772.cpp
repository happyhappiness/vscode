static void output_attr(int cnt, struct git_attr_check *check,
	const char *file)
{
	int j;
	for (j = 0; j < cnt; j++) {
		const char *value = check[j].value;

		if (ATTR_TRUE(value))
			value = "set";
		else if (ATTR_FALSE(value))
			value = "unset";
		else if (ATTR_UNSET(value))
			value = "unspecified";

		if (nul_term_line) {
			printf("%s%c" /* path */
			       "%s%c" /* attrname */
			       "%s%c" /* attrvalue */,
			       file, 0, git_attr_name(check[j].attr), 0, value, 0);
		} else {
			quote_c_style(file, NULL, stdout, 0);
			printf(": %s: %s\n", git_attr_name(check[j].attr), value);
		}

	}
}