static void compile_pcre_regexp(struct grep_pat *p, const struct grep_opt *opt)
{
	const char *error;
	int erroffset;
	int options = PCRE_MULTILINE;

	if (opt->ignore_case) {
		if (has_non_ascii(p->pattern))
			p->pcre_tables = pcre_maketables();
		options |= PCRE_CASELESS;
	}
	if (is_utf8_locale() && has_non_ascii(p->pattern))
		options |= PCRE_UTF8;

	p->pcre_regexp = pcre_compile(p->pattern, options, &error, &erroffset,
				      p->pcre_tables);
	if (!p->pcre_regexp)
		compile_regexp_failed(p, error);

	p->pcre_extra_info = pcre_study(p->pcre_regexp, 0, &error);
	if (!p->pcre_extra_info && error)
		die("%s", error);
