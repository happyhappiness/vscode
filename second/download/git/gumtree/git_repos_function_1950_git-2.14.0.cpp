static int parse_attr(const char *name, size_t len)
{
	static const struct {
		const char *name;
		size_t len;
		int val, neg;
	} attrs[] = {
#define ATTR(x, val, neg) { (x), sizeof(x)-1, (val), (neg) }
		ATTR("bold",      1, 22),
		ATTR("dim",       2, 22),
		ATTR("italic",    3, 23),
		ATTR("ul",        4, 24),
		ATTR("blink",     5, 25),
		ATTR("reverse",   7, 27),
		ATTR("strike",    9, 29)
#undef ATTR
	};
	int negate = 0;
	int i;

	if (skip_prefix_mem(name, len, "no", &name, &len)) {
		skip_prefix_mem(name, len, "-", &name, &len);
		negate = 1;
	}

	for (i = 0; i < ARRAY_SIZE(attrs); i++) {
		if (attrs[i].len == len && !memcmp(attrs[i].name, name, len))
			return negate ? attrs[i].neg : attrs[i].val;
	}
	return -1;
}