static void compile_regexp(struct grep_pat *p, struct grep_opt *opt)
{
	int err;

	p->word_regexp = opt->word_regexp;
	p->ignore_case = opt->ignore_case;

	if (opt->fixed || is_fixed(p->pattern, p->patternlen))
		p->fixed = 1;
	else
		p->fixed = 0;

	if (p->fixed) {
		if (opt->regflags & REG_ICASE || p->ignore_case)
			p->kws = kwsalloc(tolower_trans_tbl);
		else
			p->kws = kwsalloc(NULL);
		kwsincr(p->kws, p->pattern, p->patternlen);
		kwsprep(p->kws);
		return;
	}

	if (opt->pcre) {
		compile_pcre_regexp(p, opt);
		return;
	}

	err = regcomp(&p->regexp, p->pattern, opt->regflags);
	if (err) {
		char errbuf[1024];
		regerror(err, &p->regexp, errbuf, 1024);
		regfree(&p->regexp);
		compile_regexp_failed(p, errbuf);
	}
}