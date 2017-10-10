	}

	free(q->queue);
	*q = outq;
}

void diffcore_pickaxe(struct diff_options *o)
{
	const char *needle = o->pickaxe;
	int opts = o->pickaxe_opts;
	regex_t regex, *regexp = NULL;
	kwset_t kws = NULL;

	if (opts & (DIFF_PICKAXE_REGEX | DIFF_PICKAXE_KIND_G)) {
		int err;
		int cflags = REG_EXTENDED | REG_NEWLINE;
		if (DIFF_OPT_TST(o, PICKAXE_IGNORE_CASE))
			cflags |= REG_ICASE;
		err = regcomp(&regex, needle, cflags);
		if (err) {
			/* The POSIX.2 people are surely sick */
			char errbuf[1024];
			regerror(err, &regex, errbuf, 1024);
			regfree(&regex);
			die("invalid regex: %s", errbuf);
		}
		regexp = &regex;
	} else {
		kws = kwsalloc(DIFF_OPT_TST(o, PICKAXE_IGNORE_CASE)
			       ? tolower_trans_tbl : NULL);
		kwsincr(kws, needle, strlen(needle));
		kwsprep(kws);
