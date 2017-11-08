void clear_mailmap(struct string_list *map)
{
	debug_mm("mailmap: clearing %d entries...\n", map->nr);
	map->strdup_strings = 1;
	string_list_clear_func(map, free_mailmap_entry);
	debug_mm("mailmap: cleared\n");
}