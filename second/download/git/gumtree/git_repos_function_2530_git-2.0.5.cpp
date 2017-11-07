static int longest_path_match(const char *name_a, int len_a,
			      const char *name_b, int len_b,
			      int *previous_slash)
{
	int max_len, match_len = 0, match_len_prev = 0, i = 0;

	max_len = len_a < len_b ? len_a : len_b;
	while (i < max_len && name_a[i] == name_b[i]) {
		if (name_a[i] == '/') {
			match_len_prev = match_len;
			match_len = i;
		}
		i++;
	}
	/*
	 * Is 'name_b' a substring of 'name_a', the other way around,
	 * or is 'name_a' and 'name_b' the exact same string?
	 */
	if (i >= max_len && ((len_a > len_b && name_a[len_b] == '/') ||
			     (len_a < len_b && name_b[len_a] == '/') ||
			     (len_a == len_b))) {
		match_len_prev = match_len;
		match_len = i;
	}
	*previous_slash = match_len_prev;
	return match_len;
}