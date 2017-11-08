static void rsync_xal_store(item_list *xalp)
{
	item_list *new_lst = EXPAND_ITEM_LIST(&rsync_xal_l, item_list, RSYNC_XAL_LIST_INITIAL);
	/* Since the following call starts a new list, we know it will hold the
	 * entire initial-count, not just enough space for one new item. */
	*new_lst = empty_xattr;
	(void)EXPAND_ITEM_LIST(new_lst, rsync_xa, xalp->count);
	memcpy(new_lst->items, xalp->items, xalp->count * sizeof (rsync_xa));
	new_lst->count = xalp->count;
	xalp->count = 0;
}