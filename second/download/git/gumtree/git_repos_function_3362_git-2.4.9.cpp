void append_grep_pattern(struct grep_opt *opt, const char *pat,
			 const char *origin, int no, enum grep_pat_token t)
{
	append_grep_pat(opt, pat, strlen(pat), origin, no, t);
}