void append_grep_pat(struct grep_opt *opt, const char *pat, size_t patlen,
		     const char *origin, int no, enum grep_pat_token t)
{
	struct grep_pat *p = create_grep_pat(pat, patlen, origin, no, t, 0);
	do_append_grep_pat(&opt->pattern_tail, p);
}