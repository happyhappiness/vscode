static void match_racl_ids(const item_list *racl_list)
{
	int list_cnt, name_cnt;
	acl_duo *duo_item = racl_list->items;
	for (list_cnt = racl_list->count; list_cnt--; duo_item++) {
		ida_entries *idal = &duo_item->racl.names;
		id_access *ida = idal->idas;
		for (name_cnt = idal->count; name_cnt--; ida++) {
			if (ida->access & NAME_IS_USER)
				ida->id = match_uid(ida->id);
			else
				ida->id = match_gid(ida->id, NULL);
		}
	}
}