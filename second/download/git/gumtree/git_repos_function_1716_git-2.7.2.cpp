int string_list_split(struct string_list *list, const char *string,
		      int delim, int maxsplit)
{
	int count = 0;
	const char *p = string, *end;

	if (!list->strdup_strings)
		die("internal error in string_list_split(): "
		    "list->strdup_strings must be set");
	for (;;) {
		count++;
		if (maxsplit >= 0 && count > maxsplit) {
			string_list_append(list, p);
			return count;
		}
		end = strchr(p, delim);
		if (end) {
			string_list_append_nodup(list, xmemdupz(p, end - p));
			p = end + 1;
		} else {
			string_list_append(list, p);
			return count;
		}
	}
}