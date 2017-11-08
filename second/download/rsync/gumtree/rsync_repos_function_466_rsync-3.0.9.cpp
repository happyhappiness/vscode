static int find_matching_rsync_acl(const rsync_acl *racl, SMB_ACL_TYPE_T type,
				   const item_list *racl_list)
{
	static int access_match = -1, default_match = -1;
	int *match = type == SMB_ACL_TYPE_ACCESS ? &access_match : &default_match;
	size_t count = racl_list->count;

	/* If this is the first time through or we didn't match the last
	 * time, then start at the end of the list, which should be the
	 * best place to start hunting. */
	if (*match == -1)
		*match = racl_list->count - 1;
	while (count--) {
		rsync_acl *base = racl_list->items;
		if (rsync_acl_equal(base + *match, racl))
			return *match;
		if (!(*match)--)
			*match = racl_list->count - 1;
	}

	*match = -1;
	return *match;
}