static int fixmatch(struct grep_pat *p, char *line, char *eol,
		    regmatch_t *match)
{
	struct kwsmatch kwsm;
	size_t offset = kwsexec(p->kws, line, eol - line, &kwsm);
	if (offset == -1) {
		match->rm_so = match->rm_eo = -1;
		return REG_NOMATCH;
	} else {
		match->rm_so = offset;
		match->rm_eo = match->rm_so + kwsm.size[0];
		return 0;
	}
}