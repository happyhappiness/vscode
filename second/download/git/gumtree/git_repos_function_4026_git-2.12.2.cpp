static struct grep_pat *create_grep_pat(const char *pat, size_t patlen,
					const char *origin, int no,
					enum grep_pat_token t,
					enum grep_header_field field)
{
	struct grep_pat *p = xcalloc(1, sizeof(*p));
	p->pattern = xmemdupz(pat, patlen);
	p->patternlen = patlen;
	p->origin = origin;
	p->no = no;
	p->token = t;
	p->field = field;
	return p;
}