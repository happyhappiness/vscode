static int add_push_to_show_info(struct string_list_item *push_item, void *cb_data)
{
	struct show_info *show_info = cb_data;
	struct push_info *push_info = push_item->util;
	struct string_list_item *item;
	int n;
	if ((n = strlen(push_item->string)) > show_info->width)
		show_info->width = n;
	if ((n = strlen(push_info->dest)) > show_info->width2)
		show_info->width2 = n;
	item = string_list_append(show_info->list, push_item->string);
	item->util = push_item->util;
	return 0;
}