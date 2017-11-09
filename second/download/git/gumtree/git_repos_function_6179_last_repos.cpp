static int show_all(void)
{
	struct string_list list = STRING_LIST_INIT_NODUP;
	int result;

	list.strdup_strings = 1;
	result = for_each_remote(get_one_entry, &list);

	if (!result) {
		int i;

		string_list_sort(&list);
		for (i = 0; i < list.nr; i++) {
			struct string_list_item *item = list.items + i;
			if (verbose)
				printf("%s\t%s\n", item->string,
					item->util ? (const char *)item->util : "");
			else {
				if (i && !strcmp((item - 1)->string, item->string))
					continue;
				printf("%s\n", item->string);
			}
		}
	}
	string_list_clear(&list, 1);
	return result;
}