static void uncache_duo_acls(item_list *duo_list, size_t start)
{
	acl_duo *duo_item = duo_list->items;
	acl_duo *duo_start = duo_item + start;

	duo_item += duo_list->count;
	duo_list->count = start;

	while (duo_item-- > duo_start) {
		rsync_acl_free(&duo_item->racl);
		if (duo_item->sacl)
			sys_acl_free_acl(duo_item->sacl);
	}
}