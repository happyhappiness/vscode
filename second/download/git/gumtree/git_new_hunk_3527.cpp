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
	if (err) {
		char errbuf[1024];
		regerror(err, &p->regexp, errbuf, sizeof(errbuf));
		regfree(&p->regexp);
		compile_regexp_failed(p, errbuf);
	}
}

static void compile_regexp(struct grep_pat *p, struct grep_opt *opt)
{
	int icase, ascii_only;
	int err;

	p->word_regexp = opt->word_regexp;
	p->ignore_case = opt->ignore_case;
	icase	       = opt->regflags & REG_ICASE || p->ignore_case;
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
	if (opt->fixed || is_fixed(p->pattern, p->patternlen))
		p->fixed = !icase || ascii_only;
	else
		p->fixed = 0;

	if (p->fixed) {
		p->kws = kwsalloc(icase ? tolower_trans_tbl : NULL);
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

	if (opt->pcre) {
		compile_pcre_regexp(p, opt);
		return;
	}
