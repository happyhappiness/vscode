		die(_("--stateless-rpc requires multi_ack_detailed"));
	if (marked)
		for_each_ref(clear_marks, NULL);
	marked = 1;

	for_each_ref(rev_list_insert_ref_oid, NULL);
	for_each_cached_alternate(insert_one_alternate_object);

	fetching = 0;
	for ( ; refs ; refs = refs->next) {
		unsigned char *remote = refs->old_oid.hash;
		const char *remote_hex;
		struct object *o;
