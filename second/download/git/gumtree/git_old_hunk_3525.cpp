static void compile_pcre_regexp(struct grep_pat *p, const struct grep_opt *opt)
{
	const char *error;
	int erroffset;
	int options = PCRE_MULTILINE;

	if (opt->ignore_case)
		options |= PCRE_CASELESS;

	p->pcre_regexp = pcre_compile(p->pattern, options, &error, &erroffset,
			NULL);
	if (!p->pcre_regexp)
		compile_regexp_failed(p, error);

	p->pcre_extra_info = pcre_study(p->pcre_regexp, 0, &error);
	if (!p->pcre_extra_info && error)
		die("%s", error);
