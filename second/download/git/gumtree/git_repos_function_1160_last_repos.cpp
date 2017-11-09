int is_encoding_utf8(const char *name)
{
	if (!name)
		return 1;
	if (!strcasecmp(name, "utf-8") || !strcasecmp(name, "utf8"))
		return 1;
	return 0;
}