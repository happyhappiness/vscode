void string_list_remove_empty_items(struct string_list *list, int free_util) {
	filter_string_list(list, free_util, item_is_not_empty, NULL);
}