int string_list_split_in_place(struct string_list *list, char *string,
			       int delim, int maxsplit)
{
	int count = 0;
	char *p = string, *end;

	if (list->strdup_strings)
		die("internal error in string_list_split_in_place(): "
		    "list->strdup_strings must not be set");
	for (;;) {
		count++;
		if (maxsplit >= 0 && count > maxsplit) {
			string_list_append(list, p);
			return count;
		}
		end = strchr(p, delim);
		if (end) {
			*end = '\0';
			string_list_append(list, p);
			p = end + 1;
		} else {
			string_list_append(list, p);
			return count;
		}
	}
}