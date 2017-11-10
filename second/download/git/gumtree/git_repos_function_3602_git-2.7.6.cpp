static int regmatch(const regex_t *preg, char *line, char *eol,
		    regmatch_t *match, int eflags)
{
#ifdef REG_STARTEND
	match->rm_so = 0;
	match->rm_eo = eol - line;
	eflags |= REG_STARTEND;
#endif
	return regexec(preg, line, 1, match, eflags);
}