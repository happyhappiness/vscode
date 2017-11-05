static void add_strategies(const char *string, unsigned attr)
{
	struct strategy *list = NULL;
	int list_alloc = 0, list_nr = 0, i;

	memset(&list, 0, sizeof(list));
	split_merge_strategies(string, &list, &list_nr, &list_alloc);
	if (list) {
		for (i = 0; i < list_nr; i++)
			append_strategy(get_strategy(list[i].name));
		return;
	}
	for (i = 0; i < ARRAY_SIZE(all_strategy); i++)
		if (all_strategy[i].attr & attr)
			append_strategy(&all_strategy[i]);

}