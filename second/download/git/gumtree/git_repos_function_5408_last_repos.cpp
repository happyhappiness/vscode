static int parse_key_value_squoted(char *buf, struct string_list *list)
{
	while (*buf) {
		struct string_list_item *item;
		char *np;
		char *cp = strchr(buf, '=');
		if (!cp)
			return -1;
		np = strchrnul(cp, '\n');
		*cp++ = '\0';
		item = string_list_append(list, buf);

		buf = np + (*np == '\n');
		*np = '\0';
		cp = sq_dequote(cp);
		if (!cp)
			return -1;
		item->util = xstrdup(cp);
	}
	return 0;
}