static void free_rerere_id(struct string_list_item *item)
{
	free(item->util);
}