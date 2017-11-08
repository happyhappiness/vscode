static int fetch_git(struct discovery *heads,
	int nr_heads, struct ref **to_fetch)
{
	struct rpc_state rpc;
	struct strbuf preamble = STRBUF_INIT;
	char *depth_arg = NULL;
	int argc = 0, i, err;
	const char *argv[17];

	argv[argc++] = "fetch-pack";
	argv[argc++] = "--stateless-rpc";
	argv[argc++] = "--stdin";
	argv[argc++] = "--lock-pack";
	if (options.followtags)
		argv[argc++] = "--include-tag";
	if (options.thin)
		argv[argc++] = "--thin";
	if (options.verbosity >= 3) {
		argv[argc++] = "-v";
		argv[argc++] = "-v";
	}
	if (options.check_self_contained_and_connected)
		argv[argc++] = "--check-self-contained-and-connected";
	if (options.cloning)
		argv[argc++] = "--cloning";
	if (options.update_shallow)
		argv[argc++] = "--update-shallow";
	if (!options.progress)
		argv[argc++] = "--no-progress";
	if (options.depth) {
		struct strbuf buf = STRBUF_INIT;
		strbuf_addf(&buf, "--depth=%lu", options.depth);
		depth_arg = strbuf_detach(&buf, NULL);
		argv[argc++] = depth_arg;
	}
	argv[argc++] = url.buf;
	argv[argc++] = NULL;

	for (i = 0; i < nr_heads; i++) {
		struct ref *ref = to_fetch[i];
		if (!*ref->name)
			die("cannot fetch by sha1 over smart http");
		packet_buf_write(&preamble, "%s %s\n",
				 sha1_to_hex(ref->old_sha1), ref->name);
	}
	packet_buf_flush(&preamble);

	memset(&rpc, 0, sizeof(rpc));
	rpc.service_name = "git-upload-pack",
	rpc.argv = argv;
	rpc.stdin_preamble = &preamble;
	rpc.gzip_request = 1;

	err = rpc_service(&rpc, heads);
	if (rpc.result.len)
		write_or_die(1, rpc.result.buf, rpc.result.len);
	strbuf_release(&rpc.result);
	strbuf_release(&preamble);
	free(depth_arg);
	return err;
}