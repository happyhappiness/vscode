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
	if (err) {
		char errbuf[1024];
		regerror(err, &p->regexp, errbuf, sizeof(errbuf));
		regfree(&p->regexp);
		compile_regexp_failed(p, errbuf);
	}
}