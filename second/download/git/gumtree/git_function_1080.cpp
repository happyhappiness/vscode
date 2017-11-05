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