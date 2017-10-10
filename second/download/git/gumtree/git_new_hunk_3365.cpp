	return 1;
}

int cmd_receive_pack(int argc, const char **argv, const char *prefix)
{
	int advertise_refs = 0;
	struct command *commands;
	struct sha1_array shallow = SHA1_ARRAY_INIT;
	struct sha1_array ref = SHA1_ARRAY_INIT;
	struct shallow_info si;

	struct option options[] = {
		OPT__QUIET(&quiet, N_("quiet")),
		OPT_HIDDEN_BOOL(0, "stateless-rpc", &stateless_rpc, NULL),
		OPT_HIDDEN_BOOL(0, "advertise-refs", &advertise_refs, NULL),
		OPT_HIDDEN_BOOL(0, "reject-thin-pack-for-testing", &reject_thin, NULL),
		OPT_END()
	};

	packet_trace_identity("receive-pack");

	argc = parse_options(argc, argv, prefix, options, receive_pack_usage, 0);

	if (argc > 1)
		usage_msg_opt(_("Too many arguments."), receive_pack_usage, options);
	if (argc == 0)
		usage_msg_opt(_("You must specify a directory."), receive_pack_usage, options);

	service_dir = argv[0];

	setup_path();

	if (!enter_repo(service_dir, 0))
		die("'%s' does not appear to be a git repository", service_dir);

