void add_exclude(const char *string, const char *base,
		 int baselen, struct exclude_list *el, int srcpos)
{
	struct exclude *x;
	int patternlen;
	unsigned flags;
	int nowildcardlen;

	parse_exclude_pattern(&string, &patternlen, &flags, &nowildcardlen);
	if (flags & EXC_FLAG_MUSTBEDIR) {
		FLEXPTR_ALLOC_MEM(x, pattern, string, patternlen);
	} else {
		x = xmalloc(sizeof(*x));
		x->pattern = string;
	}
	x->patternlen = patternlen;
	x->nowildcardlen = nowildcardlen;
	x->base = base;
	x->baselen = baselen;
	x->flags = flags;
	x->srcpos = srcpos;
	ALLOC_GROW(el->excludes, el->nr + 1, el->alloc);
	el->excludes[el->nr++] = x;
	x->el = el;
}