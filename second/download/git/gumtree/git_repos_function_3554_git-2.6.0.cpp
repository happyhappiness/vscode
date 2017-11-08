void append_header_grep_pattern(struct grep_opt *opt,
				enum grep_header_field field, const char *pat)
{
	struct grep_pat *p = create_grep_pat(pat, strlen(pat), "header", 0,
					     GREP_PATTERN_HEAD, field);
	if (field == GREP_HEADER_REFLOG)
		opt->use_reflog_filter = 1;
	do_append_grep_pat(&opt->header_tail, p);
}