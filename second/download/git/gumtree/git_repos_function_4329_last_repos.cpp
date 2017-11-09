struct grep_opt *grep_opt_dup(const struct grep_opt *opt)
{
	struct grep_pat *pat;
	struct grep_opt *ret = xmalloc(sizeof(struct grep_opt));
	*ret = *opt;

	ret->pattern_list = NULL;
	ret->pattern_tail = &ret->pattern_list;

	for(pat = opt->pattern_list; pat != NULL; pat = pat->next)
	{
		if(pat->token == GREP_PATTERN_HEAD)
			append_header_grep_pattern(ret, pat->field,
						   pat->pattern);
		else
			append_grep_pat(ret, pat->pattern, pat->patternlen,
					pat->origin, pat->no, pat->token);
	}

	return ret;
}