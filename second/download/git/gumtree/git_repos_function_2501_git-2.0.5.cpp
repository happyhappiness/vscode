static int parse_config(unsigned int *colopts, const char *value)
{
	const char *sep = " ,";
	int group_set = 0;

	while (*value) {
		int len = strcspn(value, sep);
		if (len) {
			if (parse_option(value, len, colopts, &group_set))
				return -1;

			value += len;
		}
		value += strspn(value, sep);
	}
	/*
	 * If none of "always", "never", and "auto" is specified, then setting
	 * layout implies "always".
	 *
	 * Current value in COL_ENABLE_MASK is disregarded. This means if
	 * you set column.ui = auto and pass --column=row, then "auto"
	 * will become "always".
	 */
	if ((group_set & LAYOUT_SET) && !(group_set & ENABLE_SET))
		*colopts = (*colopts & ~COL_ENABLE_MASK) | COL_ENABLED;
	return 0;
}