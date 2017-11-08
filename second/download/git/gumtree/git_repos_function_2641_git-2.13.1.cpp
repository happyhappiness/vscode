static int match_host(const struct url_info *url_info,
		      const struct url_info *pattern_info)
{
	const char *url = url_info->url + url_info->host_off;
	const char *pat = pattern_info->url + pattern_info->host_off;
	int url_len = url_info->host_len;
	int pat_len = pattern_info->host_len;

	while (url_len && pat_len) {
		const char *url_next = end_of_token(url, '.', url_len);
		const char *pat_next = end_of_token(pat, '.', pat_len);

		if (pat_next == pat + 1 && pat[0] == '*')
			/* wildcard matches anything */
			;
		else if ((pat_next - pat) == (url_next - url) &&
			 !memcmp(url, pat, url_next - url))
			/* the components are the same */
			;
		else
			return 0; /* found an unmatch */

		if (url_next < url + url_len)
			url_next++;
		url_len -= url_next - url;
		url = url_next;
		if (pat_next < pat + pat_len)
			pat_next++;
		pat_len -= pat_next - pat;
		pat = pat_next;
	}

	return (!url_len && !pat_len);
}