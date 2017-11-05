static int list_replace_refs(const char *pattern, const char *format)
{
	struct show_data data;

	if (pattern == NULL)
		pattern = "*";
	data.pattern = pattern;

	if (format == NULL || *format == '\0' || !strcmp(format, "short"))
		data.format = REPLACE_FORMAT_SHORT;
	else if (!strcmp(format, "medium"))
		data.format = REPLACE_FORMAT_MEDIUM;
	else if (!strcmp(format, "long"))
		data.format = REPLACE_FORMAT_LONG;
	else
		die("invalid replace format '%s'\n"
		    "valid formats are 'short', 'medium' and 'long'\n",
		    format);

	for_each_replace_ref(show_reference, (void *)&data);

	return 0;
}