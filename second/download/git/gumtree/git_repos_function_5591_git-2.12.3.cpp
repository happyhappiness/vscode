static void record_person_from_buf(int which, struct string_list *people,
				   const char *buffer)
{
	char *name_buf, *name, *name_end;
	struct string_list_item *elem;
	const char *field;

	field = (which == 'a') ? "\nauthor " : "\ncommitter ";
	name = strstr(buffer, field);
	if (!name)
		return;
	name += strlen(field);
	name_end = strchrnul(name, '<');
	if (*name_end)
		name_end--;
	while (isspace(*name_end) && name <= name_end)
		name_end--;
	if (name_end < name)
		return;
	name_buf = xmemdupz(name, name_end - name + 1);

	elem = string_list_lookup(people, name_buf);
	if (!elem) {
		elem = string_list_insert(people, name_buf);
		elem->util = (void *)0;
	}
	elem->util = (void*)(util_as_integral(elem) + 1);
	free(name_buf);
}