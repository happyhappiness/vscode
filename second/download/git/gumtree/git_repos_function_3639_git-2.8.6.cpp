static int patmatch(struct grep_pat *p, char *line, char *eol,
		    regmatch_t *match, int eflags)
{
	int hit;

	if (p->fixed)
		hit = !fixmatch(p, line, eol, match);
	else if (p->pcre_regexp)
		hit = !pcrematch(p, line, eol, match, eflags);
	else
		hit = !regmatch(&p->regexp, line, eol, match, eflags);

	return hit;
}