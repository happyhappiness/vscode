static int cache_rsync_acl(rsync_acl *racl, SMB_ACL_TYPE_T type, item_list *racl_list)
{
	int ndx;

	if (!racl)
		ndx = -1;
	else if ((ndx = find_matching_rsync_acl(racl, type, racl_list)) == -1) {
		acl_duo *new_duo;
		ndx = racl_list->count;
		new_duo = EXPAND_ITEM_LIST(racl_list, acl_duo, 1000);
		new_duo->racl = *racl;
		new_duo->sacl = NULL;
		*racl = empty_rsync_acl;
	}

	return ndx;
}