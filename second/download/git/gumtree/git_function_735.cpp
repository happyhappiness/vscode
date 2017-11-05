static int pack_objects(int fd, struct ref *refs, struct sha1_array *extra, struct send_pack_args *args)
{
	/*
	 * The child becomes pack-objects --revs; we feed
	 * the revision parameters to it via its stdin and
	 * let its stdout go back to the other end.
	 */
	const char *argv[] = {
		"pack-objects",
		"--all-progress-implied",
		"--revs",
		"--stdout",
		NULL,
		NULL,
		NULL,
		NULL,
		NULL,
		NULL,
	};
	struct child_process po = CHILD_PROCESS_INIT;
	FILE *po_in;
	int i;
	int rc;

	i = 4;
	if (args->use_thin_pack)
		argv[i++] = "--thin";
	if (args->use_ofs_delta)
		argv[i++] = "--delta-base-offset";
	if (args->quiet || !args->progress)
		argv[i++] = "-q";
	if (args->progress)
		argv[i++] = "--progress";
	if (is_repository_shallow())
		argv[i++] = "--shallow";
	po.argv = argv;
	po.in = -1;
	po.out = args->stateless_rpc ? -1 : fd;
	po.git_cmd = 1;
	if (start_command(&po))
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
				break;
			send_sideband(fd, -1, buf, n, LARGE_PACKET_MAX);
		}
		free(buf);
		close(po.out);
		po.out = -1;
	}

	rc = finish_command(&po);
	if (rc) {
		/*
		 * For a normal non-zero exit, we assume pack-objects wrote
		 * something useful to stderr. For death by signal, though,
		 * we should mention it to the user. The exception is SIGPIPE
		 * (141), because that's a normal occurence if the remote end
		 * hangs up (and we'll report that by trying to read the unpack
		 * status).
		 */
		if (rc > 128 && rc != 141)
			error("pack-objects died of signal %d", rc - 128);
		return -1;
	}
	return 0;
}