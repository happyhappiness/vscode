static void add_strategies(const char *string, unsigned attr)
{
	int i;

	if (string) {
		struct string_list list = STRING_LIST_INIT_DUP;
		struct string_list_item *item;
		string_list_split(&list, string, ' ', -1);
		for_each_string_list_item(item, &list)
			append_strategy(get_strategy(item->string));
		string_list_clear(&list, 0);
		return;
	}
	for (i = 0; i < ARRAY_SIZE(all_strategy); i++)
		if (all_strategy[i].attr & attr)
			append_strategy(&all_strategy[i]);

}