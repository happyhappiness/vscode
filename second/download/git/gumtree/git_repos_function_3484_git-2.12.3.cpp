static void free_submodules_sha1s(struct string_list *submodules)
{
	struct string_list_item *item;
	for_each_string_list_item(item, submodules)
		sha1_array_clear((struct sha1_array *) item->util);
	string_list_clear(submodules, 1);
}