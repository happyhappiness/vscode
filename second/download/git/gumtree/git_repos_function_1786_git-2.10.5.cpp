struct string_list_item *string_list_append_nodup(struct string_list *list,
						  char *string)
{
	struct string_list_item *retval;
	ALLOC_GROW(list->items, list->nr + 1, list->alloc);
	retval = &list->items[list->nr++];
	retval->string = string;
	retval->util = NULL;
	return retval;
}