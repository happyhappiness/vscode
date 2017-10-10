	if (args->stateless_rpc && multi_ack == 1)
		die("--stateless-rpc requires multi_ack_detailed");
	if (marked)
		for_each_ref(clear_marks, NULL);
	marked = 1;

	for_each_ref(rev_list_insert_ref, NULL);
	for_each_alternate_ref(insert_one_alternate_ref, NULL);

	fetching = 0;
	for ( ; refs ; refs = refs->next) {
		unsigned char *remote = refs->old_sha1;
		const char *remote_hex;
