void diffcore_pickaxe(struct diff_options *o)
{
	const char *needle = o->pickaxe;
	int opts = o->pickaxe_opts;
	regex_t regex, *regexp = NULL;
	kwset_t kws = NULL;

	if (opts & (DIFF_PICKAXE_REGEX | DIFF_PICKAXE_KIND_G)) {
		int cflags = REG_EXTENDED | REG_NEWLINE;
		if (DIFF_OPT_TST(o, PICKAXE_IGNORE_CASE))
			cflags |= REG_ICASE;
		regcomp_or_die(&regex, needle, cflags);
		regexp = &regex;
	} else if (DIFF_OPT_TST(o, PICKAXE_IGNORE_CASE) &&
		   has_non_ascii(needle)) {
		struct strbuf sb = STRBUF_INIT;
		int cflags = REG_NEWLINE | REG_ICASE;

		basic_regex_quote_buf(&sb, needle);
		regcomp_or_die(&regex, sb.buf, cflags);
		strbuf_release(&sb);
		regexp = &regex;
	} else {
		kws = kwsalloc(DIFF_OPT_TST(o, PICKAXE_IGNORE_CASE)
			       ? tolower_trans_tbl : NULL);
		kwsincr(kws, needle, strlen(needle));
		kwsprep(kws);
	}

	/* Might want to warn when both S and G are on; I don't care... */
	pickaxe(&diff_queued_diff, o, regexp, kws,
		(opts & DIFF_PICKAXE_KIND_G) ? diff_grep : has_changes);

	if (regexp)
		regfree(regexp);
	else
		kwsfree(kws);
	return;
}