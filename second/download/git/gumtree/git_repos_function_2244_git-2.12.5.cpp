int git_fnmatch(const struct pathspec_item *item,
		const char *pattern, const char *string,
		int prefix)
{
	if (prefix > 0) {
		if (ps_strncmp(item, pattern, string, prefix))
			return WM_NOMATCH;
		pattern += prefix;
		string += prefix;
	}
	if (item->flags & PATHSPEC_ONESTAR) {
		int pattern_len = strlen(++pattern);
		int string_len = strlen(string);
		return string_len < pattern_len ||
			ps_strcmp(item, pattern,
				  string + string_len - pattern_len);
	}
	if (item->magic & PATHSPEC_GLOB)
		return wildmatch(pattern, string,
				 WM_PATHNAME |
				 (item->magic & PATHSPEC_ICASE ? WM_CASEFOLD : 0),
				 NULL);
	else
		/* wildmatch has not learned no FNM_PATHNAME mode yet */
		return wildmatch(pattern, string,
				 item->magic & PATHSPEC_ICASE ? WM_CASEFOLD : 0,
				 NULL);
}