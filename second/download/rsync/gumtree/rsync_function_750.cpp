static void link_idev_data(struct file_list *flist)
{
	struct file_struct *head;
	int from, to, start;

	alloc_pool_t hlink_pool;
	alloc_pool_t idev_pool = flist->hlink_pool;

	hlink_pool = pool_create(128 * 1024, sizeof (struct hlink),
	    out_of_memory, POOL_INTERN);

	for (from = to = 0; from < hlink_count; from++) {
		start = from;
		head = hlink_list[start];
		while (from < hlink_count-1
		    && LINKED(hlink_list[from], hlink_list[from+1])) {
			pool_free(idev_pool, 0, hlink_list[from]->link_u.idev);
			hlink_list[from]->link_u.links = pool_talloc(hlink_pool,
			    struct hlink, 1, "hlink_list");

			hlink_list[from]->F_HLINDEX = to;
			hlink_list[from]->F_NEXT = hlink_list[from+1];
			from++;
		}
		if (from > start) {
			pool_free(idev_pool, 0, hlink_list[from]->link_u.idev);
			hlink_list[from]->link_u.links = pool_talloc(hlink_pool,
			    struct hlink, 1, "hlink_list");

			hlink_list[from]->F_HLINDEX = to;
			hlink_list[from]->F_NEXT = head;
			hlink_list[from]->flags |= FLAG_HLINK_EOL;
			hlink_list[to++] = head;
		} else {
			pool_free(idev_pool, 0, head->link_u.idev);
			head->link_u.idev = NULL;
		}
	}

	if (!to) {
		free(hlink_list);
		hlink_list = NULL;
		pool_destroy(hlink_pool);
		hlink_pool = NULL;
	} else {
		hlink_count = to;
		if (!(hlink_list = realloc_array(hlink_list,
		    struct file_struct *, hlink_count)))
			out_of_memory("init_hard_links");
	}
	flist->hlink_pool = hlink_pool;
	pool_destroy(idev_pool);
}