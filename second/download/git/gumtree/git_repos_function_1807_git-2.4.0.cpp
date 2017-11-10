void add_exclude(const char *string, const char *base,
		 int baselen, struct exclude_list *el, int srcpos)
{
	struct exclude *x;
	int patternlen;
	int flags;
	int nowildcardlen;

	parse_exclude_pattern(&string, &patternlen, &flags, &nowildcardlen);
	if (flags & EXC_FLAG_MUSTBEDIR) {
		char *s;
		x = xmalloc(sizeof(*x) + patternlen + 1);
		s = (char *)(x+1);
		memcpy(s, string, patternlen);
		s[patternlen] = '\0';
		x->pattern = s;
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