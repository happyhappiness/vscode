static void compile_regexp(struct grep_pat *p, struct grep_opt *opt)
{
	int ascii_only;
	int err;
	int regflags = REG_NEWLINE;

	p->word_regexp = opt->word_regexp;
	p->ignore_case = opt->ignore_case;
	ascii_only     = !has_non_ascii(p->pattern);

	/*
	 * Even when -F (fixed) asks us to do a non-regexp search, we
	 * may not be able to correctly case-fold when -i
	 * (ignore-case) is asked (in which case, we'll synthesize a
	 * regexp to match the pattern that matches regexp special
	 * characters literally, while ignoring case differences).  On
	 * the other hand, even without -F, if the pattern does not
	 * have any regexp special characters and there is no need for
	 * case-folding search, we can internally turn it into a
	 * simple string match using kws.  p->fixed tells us if we
	 * want to use kws.
	 */
	if (opt->fixed ||
	    has_null(p->pattern, p->patternlen) ||
	    is_fixed(p->pattern, p->patternlen))
		p->fixed = !p->ignore_case || ascii_only;

	if (p->fixed) {
		p->kws = kwsalloc(p->ignore_case ? tolower_trans_tbl : NULL);
		kwsincr(p->kws, p->pattern, p->patternlen);
		kwsprep(p->kws);
		return;
	} else if (opt->fixed) {
		/*
		 * We come here when the pattern has the non-ascii
		 * characters we cannot case-fold, and asked to
		 * ignore-case.
		 */
		compile_fixed_regexp(p, opt);
		return;
	}

	if (opt->pcre2) {
		compile_pcre2_pattern(p, opt);
		return;
	}

	if (opt->pcre1) {
		compile_pcre1_regexp(p, opt);
		return;
	}

	if (p->ignore_case)
		regflags |= REG_ICASE;
	if (opt->extended_regexp_option)
		regflags |= REG_EXTENDED;
	err = regcomp(&p->regexp, p->pattern, regflags);
	if (err) {
		char errbuf[1024];
		regerror(err, &p->regexp, errbuf, 1024);
		regfree(&p->regexp);
		compile_regexp_failed(p, errbuf);
	}
}