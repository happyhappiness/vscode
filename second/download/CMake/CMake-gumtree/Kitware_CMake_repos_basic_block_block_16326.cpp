{
	int r;

	(void)ffmax; /* UNUSED */

	r = idr_ensure_poolsize(a, idr, cnt);
	if (r != ARCHIVE_OK)
		return (r);
	__archive_rb_tree_init(&(idr->rbtree), rbt_ops);
	idr->wait_list.first = NULL;
	idr->wait_list.last = &(idr->wait_list.first);
	idr->pool_idx = 0;
	idr->num_size = num_size;
	idr->null_size = null_size;
	return (ARCHIVE_OK);
}