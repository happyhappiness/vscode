static inline int upstream_mark(const char *string, int len)
{
	const char *suffix[] = { "@{upstream}", "@{u}" };
	return at_mark(string, len, suffix, ARRAY_SIZE(suffix));
}