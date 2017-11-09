static inline int push_mark(const char *string, int len)
{
	const char *suffix[] = { "@{push}" };
	return at_mark(string, len, suffix, ARRAY_SIZE(suffix));
}