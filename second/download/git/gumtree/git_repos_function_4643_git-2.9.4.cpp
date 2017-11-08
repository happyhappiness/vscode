static int fuzzy_matchlines(const char *s1, size_t n1,
			    const char *s2, size_t n2)
{
	const char *last1 = s1 + n1 - 1;
	const char *last2 = s2 + n2 - 1;
	int result = 0;

	/* ignore line endings */
	while ((*last1 == '\r') || (*last1 == '\n'))
		last1--;
	while ((*last2 == '\r') || (*last2 == '\n'))
		last2--;

	/* skip leading whitespaces, if both begin with whitespace */
	if (s1 <= last1 && s2 <= last2 && isspace(*s1) && isspace(*s2)) {
		while (isspace(*s1) && (s1 <= last1))
			s1++;
		while (isspace(*s2) && (s2 <= last2))
			s2++;
	}
	/* early return if both lines are empty */
	if ((s1 > last1) && (s2 > last2))
		return 1;
	while (!result) {
		result = *s1++ - *s2++;
		/*
		 * Skip whitespace inside. We check for whitespace on
		 * both buffers because we don't want "a b" to match
		 * "ab"
		 */
		if (isspace(*s1) && isspace(*s2)) {
			while (isspace(*s1) && s1 <= last1)
				s1++;
			while (isspace(*s2) && s2 <= last2)
				s2++;
		}
		/*
		 * If we reached the end on one side only,
		 * lines don't match
		 */
		if (
		    ((s2 > last2) && (s1 <= last1)) ||
		    ((s1 > last1) && (s2 <= last2)))
			return 0;
		if ((s1 > last1) && (s2 > last2))
			break;
	}

	return !result;
}