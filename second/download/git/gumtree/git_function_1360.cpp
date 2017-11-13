static void compile_pcre2_pattern(struct grep_pat *p, const struct grep_opt *opt)
{
	int error;
	PCRE2_UCHAR errbuf[256];
	PCRE2_SIZE erroffset;
	int options = PCRE2_MULTILINE;
	const uint8_t *character_tables = NULL;
	int jitret;

	assert(opt->pcre2);

	p->pcre2_compile_context = NULL;

	if (opt->ignore_case) {
		if (has_non_ascii(p->pattern)) {
			character_tables = pcre2_maketables(NULL);
			p->pcre2_compile_context = pcre2_compile_context_create(NULL);
			pcre2_set_character_tables(p->pcre2_compile_context, character_tables);
		}
		options |= PCRE2_CASELESS;
	}
	if (is_utf8_locale() && has_non_ascii(p->pattern))
		options |= PCRE2_UTF;

	p->pcre2_pattern = pcre2_compile((PCRE2_SPTR)p->pattern,
					 p->patternlen, options, &error, &erroffset,
					 p->pcre2_compile_context);

	if (p->pcre2_pattern) {
		p->pcre2_match_data = pcre2_match_data_create_from_pattern(p->pcre2_pattern, NULL);
		if (!p->pcre2_match_data)
			die("Couldn't allocate PCRE2 match data");
	} else {
		pcre2_get_error_message(error, errbuf, sizeof(errbuf));
		compile_regexp_failed(p, (const char *)&errbuf);
	}

	pcre2_config(PCRE2_CONFIG_JIT, &p->pcre2_jit_on);
	if (p->pcre2_jit_on == 1) {
		jitret = pcre2_jit_compile(p->pcre2_pattern, PCRE2_JIT_COMPLETE);
		if (jitret)
			die("Couldn't JIT the PCRE2 pattern '%s', got '%d'\n", p->pattern, jitret);
		p->pcre2_jit_stack = pcre2_jit_stack_create(1, 1024 * 1024, NULL);
		if (!p->pcre2_jit_stack)
			die("Couldn't allocate PCRE2 JIT stack");
		p->pcre2_match_context = pcre2_match_context_create(NULL);
		if (!p->pcre2_match_context)
			die("Couldn't allocate PCRE2 match context");
		pcre2_jit_stack_assign(p->pcre2_match_context, NULL, p->pcre2_jit_stack);
	} else if (p->pcre2_jit_on != 0) {
		die("BUG: The pcre2_jit_on variable should be 0 or 1, not %d",
		    p->pcre1_jit_on);
	}
}