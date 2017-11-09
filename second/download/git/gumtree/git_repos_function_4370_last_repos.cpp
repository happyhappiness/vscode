static int patmatch(struct grep_pat *p, char *line, char *eol,
		    regmatch_t *match, int eflags)
{
	int hit;

	if (p->fixed)
		hit = !fixmatch(p, line, eol, match);
	else if (p->pcre1_regexp)
		hit = !pcre1match(p, line, eol, match, eflags);
	else if (p->pcre2_pattern)
		hit = !pcre2match(p, line, eol, match, eflags);
	else
		hit = !regexec_buf(&p->regexp, line, eol - line, 1, match,
				   eflags);

	return hit;
}