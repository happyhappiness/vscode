static void link_idev_data(void)
{
	int32 cur, from, to, start;

	alloc_pool_t hlink_pool;
	alloc_pool_t idev_pool = the_file_list->hlink_pool;

	hlink_pool = pool_create(128 * 1024, sizeof (struct hlink),
	    out_of_memory, POOL_INTERN);

	for (from = to = 0; from < hlink_count; from++) {
		start = from;
		while (1) {
			cur = hlink_list[from];
			if (from == hlink_count-1
			    || !LINKED(cur, hlink_list[from+1]))
				break;
			pool_free(idev_pool, 0, FPTR(cur)->link_u.idev);
			FPTR(cur)->link_u.links = pool_talloc(hlink_pool,
			    struct hlink, 1, "hlink_list");

			FPTR(cur)->F_HLINDEX = to;
			FPTR(cur)->F_NEXT = hlink_list[++from];
			FPTR(cur)->link_u.links->link_dest_used = 0;
		}
		pool_free(idev_pool, 0, FPTR(cur)->link_u.idev);
		if (from > start) {
			int head = hlink_list[start];
			FPTR(cur)->link_u.links = pool_talloc(hlink_pool,
			    struct hlink, 1, "hlink_list");

			FPTR(head)->flags |= FLAG_HLINK_TOL;
			FPTR(cur)->F_HLINDEX = to;
			FPTR(cur)->F_NEXT = head;
			FPTR(cur)->flags |= FLAG_HLINK_EOL;
			FPTR(cur)->link_u.links->link_dest_used = 0;
			hlink_list[to++] = head;
		} else
			FPTR(cur)->link_u.links = NULL;
	}

	if (!to) {
		free(hlink_list);
		hlink_list = NULL;
		pool_destroy(hlink_pool);
		hlink_pool = NULL;
	} else {
		hlink_count = to;
		hlink_list = realloc_array(hlink_list, int32, hlink_count);
		if (!hlink_list)
			out_of_memory("init_hard_links");
	}
	the_file_list->hlink_pool = hlink_pool;
	pool_destroy(idev_pool);
}