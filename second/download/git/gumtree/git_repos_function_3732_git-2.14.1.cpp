static void free_submodules_oids(struct string_list *submodules)
{
	struct string_list_item *item;
	for_each_string_list_item(item, submodules)
		oid_array_clear((struct oid_array *) item->util);
	string_list_clear(submodules, 1);
}