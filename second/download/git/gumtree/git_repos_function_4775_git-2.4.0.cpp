static void add_header(const char *value)
{
	struct string_list_item *item;
	int len = strlen(value);
	while (len && value[len - 1] == '\n')
		len--;

	if (!strncasecmp(value, "to: ", 4)) {
		item = string_list_append(&extra_to, value + 4);
		len -= 4;
	} else if (!strncasecmp(value, "cc: ", 4)) {
		item = string_list_append(&extra_cc, value + 4);
		len -= 4;
	} else {
		item = string_list_append(&extra_hdr, value);
	}

	item->string[len] = '\0';
}