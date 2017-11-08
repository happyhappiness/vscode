static void find_better_matching_suffix(const char *tagname, const char *suffix,
					int suffix_len, int start, int conf_pos,
					struct suffix_match *match)
{
	/*
	 * A better match either starts earlier or starts at the same offset
	 * but is longer.
	 */
	int end = match->len < suffix_len ? match->start : match->start-1;
	int i;
	for (i = start; i <= end; i++)
		if (starts_with(tagname + i, suffix)) {
			match->conf_pos = conf_pos;
			match->start = i;
			match->len = suffix_len;
			break;
		}
}