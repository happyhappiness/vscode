
static int fetch_git(struct discovery *heads,
	int nr_heads, struct ref **to_fetch)
{
	struct rpc_state rpc;
	struct strbuf preamble = STRBUF_INIT;
	int i, err;
	struct argv_array args = ARGV_ARRAY_INIT;

	argv_array_pushl(&args, "fetch-pack", "--stateless-rpc",
			 "--stdin", "--lock-pack", NULL);
	if (options.followtags)
		argv_array_push(&args, "--include-tag");
	if (options.thin)
		argv_array_push(&args, "--thin");
	if (options.verbosity >= 3)
		argv_array_pushl(&args, "-v", "-v", NULL);
	if (options.check_self_contained_and_connected)
		argv_array_push(&args, "--check-self-contained-and-connected");
	if (options.cloning)
		argv_array_push(&args, "--cloning");
	if (options.update_shallow)
		argv_array_push(&args, "--update-shallow");
	if (!options.progress)
		argv_array_push(&args, "--no-progress");
	if (options.depth)
		argv_array_pushf(&args, "--depth=%lu", options.depth);
	if (options.deepen_since)
		argv_array_pushf(&args, "--shallow-since=%s", options.deepen_since);
	for (i = 0; i < options.deepen_not.nr; i++)
		argv_array_pushf(&args, "--shallow-exclude=%s",
				 options.deepen_not.items[i].string);
	if (options.deepen_relative && options.depth)
		argv_array_push(&args, "--deepen-relative");
	argv_array_push(&args, url.buf);

	for (i = 0; i < nr_heads; i++) {
		struct ref *ref = to_fetch[i];
		if (!*ref->name)
			die("cannot fetch by sha1 over smart http");
		packet_buf_write(&preamble, "%s %s\n",
				 oid_to_hex(&ref->old_oid), ref->name);
	}
	packet_buf_flush(&preamble);

	memset(&rpc, 0, sizeof(rpc));
	rpc.service_name = "git-upload-pack",
	rpc.argv = args.argv;
	rpc.stdin_preamble = &preamble;
	rpc.gzip_request = 1;

	err = rpc_service(&rpc, heads);
	if (rpc.result.len)
		write_or_die(1, rpc.result.buf, rpc.result.len);
	strbuf_release(&rpc.result);
	strbuf_release(&preamble);
	argv_array_clear(&args);
	return err;
}

static int fetch(int nr_heads, struct ref **to_fetch)
{
	struct discovery *d = discover_refs("git-upload-pack", 0);
