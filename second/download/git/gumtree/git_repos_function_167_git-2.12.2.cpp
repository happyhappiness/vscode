int cmd_main(int argc, const char **argv)
{
	const char *dir;
	int strict = 0;
	struct option options[] = {
		OPT_BOOL(0, "stateless-rpc", &stateless_rpc,
			 N_("quit after a single request/response exchange")),
		OPT_BOOL(0, "advertise-refs", &advertise_refs,
			 N_("exit immediately after initial ref advertisement")),
		OPT_BOOL(0, "strict", &strict,
			 N_("do not try <directory>/.git/ if <directory> is no Git directory")),
		OPT_INTEGER(0, "timeout", &timeout,
			    N_("interrupt transfer after <n> seconds of inactivity")),
		OPT_END()
	};

	packet_trace_identity("upload-pack");
	check_replace_refs = 0;

	argc = parse_options(argc, argv, NULL, options, upload_pack_usage, 0);

	if (argc != 1)
		usage_with_options(upload_pack_usage, options);

	if (timeout)
		daemon_mode = 1;

	setup_path();

	dir = argv[0];

	if (!enter_repo(dir, strict))
		die("'%s' does not appear to be a git repository", dir);

	git_config(upload_pack_config, NULL);
	upload_pack();
	return 0;
}