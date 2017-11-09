static void compile_pcre1_regexp(struct grep_pat *p, const struct grep_opt *opt)
{
	const char *error;
	int erroffset;
	int options = PCRE_MULTILINE;

	if (opt->ignore_case) {
		if (has_non_ascii(p->pattern))
			p->pcre1_tables = pcre_maketables();
		options |= PCRE_CASELESS;
	}
	if (is_utf8_locale() && has_non_ascii(p->pattern))
		options |= PCRE_UTF8;

	p->pcre1_regexp = pcre_compile(p->pattern, options, &error, &erroffset,
				      p->pcre1_tables);
	if (!p->pcre1_regexp)
		compile_regexp_failed(p, error);

	p->pcre1_extra_info = pcre_study(p->pcre1_regexp, PCRE_STUDY_JIT_COMPILE, &error);
	if (!p->pcre1_extra_info && error)
		die("%s", error);

#ifdef GIT_PCRE1_USE_JIT
	pcre_config(PCRE_CONFIG_JIT, &p->pcre1_jit_on);
	if (p->pcre1_jit_on == 1) {
		p->pcre1_jit_stack = pcre_jit_stack_alloc(1, 1024 * 1024);
		if (!p->pcre1_jit_stack)
			die("Couldn't allocate PCRE JIT stack");
		pcre_assign_jit_stack(p->pcre1_extra_info, NULL, p->pcre1_jit_stack);
	} else if (p->pcre1_jit_on != 0) {
		die("BUG: The pcre1_jit_on variable should be 0 or 1, not %d",
		    p->pcre1_jit_on);
	}
#endif
}