static int look_ahead(struct grep_opt *opt,
		      unsigned long *left_p,
		      unsigned *lno_p,
		      char **bol_p)
{
	unsigned lno = *lno_p;
	char *bol = *bol_p;
	struct grep_pat *p;
	char *sp, *last_bol;
	regoff_t earliest = -1;

	for (p = opt->pattern_list; p; p = p->next) {
		int hit;
		regmatch_t m;

		hit = patmatch(p, bol, bol + *left_p, &m, 0);
		if (!hit || m.rm_so < 0 || m.rm_eo < 0)
			continue;
		if (earliest < 0 || m.rm_so < earliest)
			earliest = m.rm_so;
	}

	if (earliest < 0) {
		*bol_p = bol + *left_p;
		*left_p = 0;
		return 1;
	}
	for (sp = bol + earliest; bol < sp && sp[-1] != '\n'; sp--)
		; /* find the beginning of the line */
	last_bol = sp;

	for (sp = bol; sp < last_bol; sp++) {
		if (*sp == '\n')
			lno++;
	}
	*left_p -= last_bol - bol;
	*bol_p = last_bol;
	*lno_p = lno;
	return 0;
}