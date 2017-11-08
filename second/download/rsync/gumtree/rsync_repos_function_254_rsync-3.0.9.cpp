void uncache_tmp_xattrs(void)
{
	if (prior_xattr_count != (size_t)-1) {
		item_list *xattr_item = rsync_xal_l.items;
		item_list *xattr_start = xattr_item + prior_xattr_count;
		xattr_item += rsync_xal_l.count;
		rsync_xal_l.count = prior_xattr_count;
		while (xattr_item-- > xattr_start)
			rsync_xal_free(xattr_item);
		prior_xattr_count = (size_t)-1;
	}
}