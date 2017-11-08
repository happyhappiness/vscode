static int swap_prereleases(const char *s1,
			    const char *s2,
			    int off,
			    int *diff)
{
	int i;
	struct suffix_match match1 = { -1, off, -1 };
	struct suffix_match match2 = { -1, off, -1 };

	for (i = 0; i < prereleases->nr; i++) {
		const char *suffix = prereleases->items[i].string;
		int start, suffix_len = strlen(suffix);
		if (suffix_len < off)
			start = off - suffix_len;
		else
			start = 0;
		find_better_matching_suffix(s1, suffix, suffix_len, start,
					    i, &match1);
		find_better_matching_suffix(s2, suffix, suffix_len, start,
					    i, &match2);
	}
	if (match1.conf_pos == -1 && match2.conf_pos == -1)
		return 0;
	if (match1.conf_pos == match2.conf_pos)
		/* Found the same suffix in both, e.g. "-rc" in "v1.0-rcX"
		 * and "v1.0-rcY": the caller should decide based on "X"
		 * and "Y". */
		return 0;

	if (match1.conf_pos >= 0 && match2.conf_pos >= 0)
		*diff = match1.conf_pos - match2.conf_pos;
	else if (match1.conf_pos >= 0)
		*diff = -1;
	else /* if (match2.conf_pos >= 0) */
		*diff = 1;
	return 1;
}