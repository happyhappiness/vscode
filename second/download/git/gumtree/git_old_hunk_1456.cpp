	else
		where[0] = 0;

	die("%s'%s': %s", where, p->pattern, error);
}

#ifdef USE_LIBPCRE
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
}

static int pcrematch(struct grep_pat *p, const char *line, const char *eol,
		regmatch_t *match, int eflags)
{
	int ovector[30], ret, flags = 0;

	if (eflags & REG_NOTBOL)
		flags |= PCRE_NOTBOL;

	ret = pcre_exec(p->pcre_regexp, p->pcre_extra_info, line, eol - line,
			0, flags, ovector, ARRAY_SIZE(ovector));
	if (ret < 0 && ret != PCRE_ERROR_NOMATCH)
		die("pcre_exec failed with error code %d", ret);
	if (ret > 0) {
		ret = 0;
		match->rm_so = ovector[0];
		match->rm_eo = ovector[1];
	}

	return ret;
}

static void free_pcre_regexp(struct grep_pat *p)
{
	pcre_free(p->pcre_regexp);
	pcre_free(p->pcre_extra_info);
	pcre_free((void *)p->pcre_tables);
}
#else /* !USE_LIBPCRE */
static void compile_pcre_regexp(struct grep_pat *p, const struct grep_opt *opt)
{
	die("cannot use Perl-compatible regexes when not compiled with USE_LIBPCRE");
}

static int pcrematch(struct grep_pat *p, const char *line, const char *eol,
		regmatch_t *match, int eflags)
{
	return 1;
}

static void free_pcre_regexp(struct grep_pat *p)
{
}
#endif /* !USE_LIBPCRE */

static int is_fixed(const char *s, size_t len)
{
	size_t i;

	/* regcomp cannot accept patterns with NULs so we
	 * consider any pattern containing a NUL fixed.
	 */
	if (memchr(s, 0, len))
		return 1;

	for (i = 0; i < len; i++) {
		if (is_regex_special(s[i]))
			return 0;
	}

	return 1;
}

static void compile_fixed_regexp(struct grep_pat *p, struct grep_opt *opt)
{
	struct strbuf sb = STRBUF_INIT;
	int err;
	int regflags;

	basic_regex_quote_buf(&sb, p->pattern);
	regflags = opt->regflags & ~REG_EXTENDED;
	if (opt->ignore_case)
		regflags |= REG_ICASE;
	err = regcomp(&p->regexp, sb.buf, regflags);
	if (opt->debug)
		fprintf(stderr, "fixed %s\n", sb.buf);
	strbuf_release(&sb);
