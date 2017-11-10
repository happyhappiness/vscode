static int item_is_not_empty(struct string_list_item *item, void *unused)
{
	return *item->string != '\0';
}