	else
		where[0] = 0;

	die("%s'%s': %s", where, p->pattern, error);
}

static int is_fixed(const char *s, size_t len)
{
	size_t i;

	for (i = 0; i < len; i++) {
		if (is_regex_special(s[i]))
			return 0;
	}

	return 1;
}

static int has_null(const char *s, size_t len)
{
	/*
	 * regcomp cannot accept patterns with NULs so when using it
	 * we consider any pattern containing a NUL fixed.
	 */
	if (memchr(s, 0, len))
		return 1;

	return 0;
}

#ifdef USE_LIBPCRE1
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

static void free_pcre1_regexp(struct grep_pat *p)
{
	pcre_free(p->pcre1_regexp);
#ifdef GIT_PCRE1_USE_JIT
	if (p->pcre1_jit_on) {
		pcre_free_study(p->pcre1_extra_info);
		pcre_jit_stack_free(p->pcre1_jit_stack);
	} else
#endif
	{
		pcre_free(p->pcre1_extra_info);
	}
	pcre_free((void *)p->pcre1_tables);
}
#else /* !USE_LIBPCRE1 */
static void compile_pcre1_regexp(struct grep_pat *p, const struct grep_opt *opt)
{
	die("cannot use Perl-compatible regexes when not compiled with USE_LIBPCRE");
}

static int pcre1match(struct grep_pat *p, const char *line, const char *eol,
		regmatch_t *match, int eflags)
{
	return 1;
}

static void free_pcre1_regexp(struct grep_pat *p)
{
}
#endif /* !USE_LIBPCRE1 */

#ifdef USE_LIBPCRE2
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

static int pcre2match(struct grep_pat *p, const char *line, const char *eol,
		regmatch_t *match, int eflags)
{
	int ret, flags = 0;
	PCRE2_SIZE *ovector;
	PCRE2_UCHAR errbuf[256];

	if (eflags & REG_NOTBOL)
		flags |= PCRE2_NOTBOL;

	if (p->pcre2_jit_on)
		ret = pcre2_jit_match(p->pcre2_pattern, (unsigned char *)line,
				      eol - line, 0, flags, p->pcre2_match_data,
				      NULL);
	else
		ret = pcre2_match(p->pcre2_pattern, (unsigned char *)line,
				  eol - line, 0, flags, p->pcre2_match_data,
				  NULL);

	if (ret < 0 && ret != PCRE2_ERROR_NOMATCH) {
		pcre2_get_error_message(ret, errbuf, sizeof(errbuf));
		die("%s failed with error code %d: %s",
		    (p->pcre2_jit_on ? "pcre2_jit_match" : "pcre2_match"), ret,
		    errbuf);
	}
	if (ret > 0) {
		ovector = pcre2_get_ovector_pointer(p->pcre2_match_data);
		ret = 0;
		match->rm_so = (int)ovector[0];
		match->rm_eo = (int)ovector[1];
	}

	return ret;
}

static void free_pcre2_pattern(struct grep_pat *p)
{
	pcre2_compile_context_free(p->pcre2_compile_context);
	pcre2_code_free(p->pcre2_pattern);
	pcre2_match_data_free(p->pcre2_match_data);
	pcre2_jit_stack_free(p->pcre2_jit_stack);
	pcre2_match_context_free(p->pcre2_match_context);
}
#else /* !USE_LIBPCRE2 */
static void compile_pcre2_pattern(struct grep_pat *p, const struct grep_opt *opt)
{
	/*
	 * Unreachable until USE_LIBPCRE2 becomes synonymous with
	 * USE_LIBPCRE. See the sibling comment in
	 * grep_set_pattern_type_option().
	 */
	die("cannot use Perl-compatible regexes when not compiled with USE_LIBPCRE");
}

static int pcre2match(struct grep_pat *p, const char *line, const char *eol,
		regmatch_t *match, int eflags)
{
	return 1;
}

static void free_pcre2_pattern(struct grep_pat *p)
{
}
#endif /* !USE_LIBPCRE2 */

static void compile_fixed_regexp(struct grep_pat *p, struct grep_opt *opt)
{
	struct strbuf sb = STRBUF_INIT;
	int err;
	int regflags = 0;

	basic_regex_quote_buf(&sb, p->pattern);
	if (opt->ignore_case)
		regflags |= REG_ICASE;
	err = regcomp(&p->regexp, sb.buf, regflags);
	if (opt->debug)
		fprintf(stderr, "fixed %s\n", sb.buf);
	strbuf_release(&sb);
