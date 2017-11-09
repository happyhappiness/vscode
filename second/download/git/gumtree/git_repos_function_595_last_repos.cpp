static void find_longest_prefix(struct strbuf *out, const char *pattern)
{
	const char *p;

	for (p = pattern; *p && !is_glob_special(*p); p++)
		;

	strbuf_add(out, pattern, p - pattern);
}