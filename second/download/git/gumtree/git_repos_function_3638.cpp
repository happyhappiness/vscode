static const char *alias_url(const char *url, struct rewrites *r)
{
	int i, j;
	char *ret;
	struct counted_string *longest;
	int longest_i;

	longest = NULL;
	longest_i = -1;
	for (i = 0; i < r->rewrite_nr; i++) {
		if (!r->rewrite[i])
			continue;
		for (j = 0; j < r->rewrite[i]->instead_of_nr; j++) {
			if (starts_with(url, r->rewrite[i]->instead_of[j].s) &&
			    (!longest ||
			     longest->len < r->rewrite[i]->instead_of[j].len)) {
				longest = &(r->rewrite[i]->instead_of[j]);
				longest_i = i;
			}
		}
	}
	if (!longest)
		return url;

	ret = xmalloc(r->rewrite[longest_i]->baselen +
		     (strlen(url) - longest->len) + 1);
	strcpy(ret, r->rewrite[longest_i]->base);
	strcpy(ret + r->rewrite[longest_i]->baselen, url + longest->len);
	return ret;
}