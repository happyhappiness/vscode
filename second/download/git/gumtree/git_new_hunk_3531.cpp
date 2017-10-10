		die_errno("git pack-objects failed");

	/*
	 * We feed the pack-objects we just spawned with revision
	 * parameters by writing to the pipe.
	 */
	po_in = xfdopen(po.in, "w");
	for (i = 0; i < extra->nr; i++)
		feed_object(extra->sha1[i], po_in, 1);

	while (refs) {
		if (!is_null_oid(&refs->old_oid))
			feed_object(refs->old_oid.hash, po_in, 1);
		if (!is_null_oid(&refs->new_oid))
			feed_object(refs->new_oid.hash, po_in, 0);
		refs = refs->next;
	}

	fflush(po_in);
	if (ferror(po_in))
		die_errno("error writing to pack-objects");
	fclose(po_in);

	if (args->stateless_rpc) {
		char *buf = xmalloc(LARGE_PACKET_MAX);
		while (1) {
			ssize_t n = xread(po.out, buf, LARGE_PACKET_MAX);
			if (n <= 0)
