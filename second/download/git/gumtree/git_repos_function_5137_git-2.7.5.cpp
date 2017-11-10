static size_t expand_format(struct strbuf *sb, const char *start, void *data)
{
	const char *end;

	if (*start != '(')
		return 0;
	end = strchr(start + 1, ')');
	if (!end)
		die("format element '%s' does not end in ')'", start);

	expand_atom(sb, start + 1, end - start - 1, data);

	return end - start + 1;
}