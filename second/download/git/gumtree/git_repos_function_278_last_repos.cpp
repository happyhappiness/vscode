static int remove_available_paths(struct string_list_item *item, void *cb_data)
{
	struct string_list *available_paths = cb_data;
	struct string_list_item *available;

	available = string_list_lookup(available_paths, item->string);
	if (available)
		available->util = (void *)item->string;
	return !available;
}