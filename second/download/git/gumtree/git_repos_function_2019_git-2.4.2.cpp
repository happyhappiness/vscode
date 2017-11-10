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
	int i;

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
	for (i = 0; i < extra->nr; i++)
		if (!feed_object(extra->sha1[i], po.in, 1))
			break;

	while (refs) {
		if (!is_null_sha1(refs->old_sha1) &&
		    !feed_object(refs->old_sha1, po.in, 1))
			break;
		if (!is_null_sha1(refs->new_sha1) &&
		    !feed_object(refs->new_sha1, po.in, 0))
			break;
		refs = refs->next;
	}

	close(po.in);

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

	if (finish_command(&po))
		return -1;
	return 0;
}