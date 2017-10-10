		die_errno("git pack-objects failed");

	/*
	 * We feed the pack-objects we just spawned with revision
	 * parameters by writing to the pipe.
	 */
	for (i = 0; i < extra->nr; i++)
		if (!feed_object(extra->sha1[i], po.in, 1))
			break;

	while (refs) {
		if (!is_null_oid(&refs->old_oid) &&
		    !feed_object(refs->old_oid.hash, po.in, 1))
			break;
		if (!is_null_oid(&refs->new_oid) &&
		    !feed_object(refs->new_oid.hash, po.in, 0))
			break;
		refs = refs->next;
	}

	close(po.in);

	if (args->stateless_rpc) {
		char *buf = xmalloc(LARGE_PACKET_MAX);
		while (1) {
			ssize_t n = xread(po.out, buf, LARGE_PACKET_MAX);
			if (n <= 0)
