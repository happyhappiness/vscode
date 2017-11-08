static int pcre1match(struct grep_pat *p, const char *line, const char *eol,
		regmatch_t *match, int eflags)
{
	int ovector[30], ret, flags = 0;

	if (eflags & REG_NOTBOL)
		flags |= PCRE_NOTBOL;

#ifdef GIT_PCRE1_USE_JIT
	if (p->pcre1_jit_on) {
		ret = pcre_jit_exec(p->pcre1_regexp, p->pcre1_extra_info, line,
				    eol - line, 0, flags, ovector,
				    ARRAY_SIZE(ovector), p->pcre1_jit_stack);
	} else
#endif
	{
		ret = pcre_exec(p->pcre1_regexp, p->pcre1_extra_info, line,
				eol - line, 0, flags, ovector,
				ARRAY_SIZE(ovector));
	}

	if (ret < 0 && ret != PCRE_ERROR_NOMATCH)
		die("pcre_exec failed with error code %d", ret);
	if (ret > 0) {
		ret = 0;
		match->rm_so = ovector[0];
		match->rm_eo = ovector[1];
	}

	return ret;
}