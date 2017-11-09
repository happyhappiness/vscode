static int parse_cat_response_line(const char *header, off_t *len)
{
	uintmax_t n;
	const char *type;
	const char *end;

	if (ends_with(header, " missing"))
		return error("cat-blob reports missing blob: %s", header);
	type = strstr(header, " blob ");
	if (!type)
		return error("cat-blob header has wrong object type: %s", header);
	n = strtoumax(type + strlen(" blob "), (char **) &end, 10);
	if (end == type + strlen(" blob "))
		return error("cat-blob header does not contain length: %s", header);
	if (memchr(type + strlen(" blob "), '-', end - type - strlen(" blob ")))
		return error("cat-blob header contains negative length: %s", header);
	if (n == UINTMAX_MAX || n > maximum_signed_value_of_type(off_t))
		return error("blob too large for current definition of off_t");
	*len = n;
	if (*end)
		return error("cat-blob header contains garbage after length: %s", header);
	return 0;
}