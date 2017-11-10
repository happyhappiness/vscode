int cmd_send_pack(int argc, const char **argv, const char *prefix)
{
	int i, nr_refspecs = 0;
	const char **refspecs = NULL;
	const char *remote_name = NULL;
	struct remote *remote = NULL;
	const char *dest = NULL;
	int fd[2];
	struct child_process *conn;
	struct sha1_array extra_have = SHA1_ARRAY_INIT;
	struct sha1_array shallow = SHA1_ARRAY_INIT;
	struct ref *remote_refs, *local_refs;
	int ret;
	int helper_status = 0;
	int send_all = 0;
	int verbose = 0;
	const char *receivepack = "git-receive-pack";
	unsigned dry_run = 0;
	unsigned send_mirror = 0;
	unsigned force_update = 0;
	unsigned quiet = 0;
	int push_cert = 0;
	unsigned use_thin_pack = 0;
	unsigned atomic = 0;
	unsigned stateless_rpc = 0;
	int flags;
	unsigned int reject_reasons;
	int progress = -1;
	int from_stdin = 0;
	struct push_cas_option cas = {0};

	struct option options[] = {
		OPT__VERBOSITY(&verbose),
		OPT_STRING(0, "receive-pack", &receivepack, "receive-pack", N_("receive pack program")),
		OPT_STRING(0, "exec", &receivepack, "receive-pack", N_("receive pack program")),
		OPT_STRING(0, "remote", &remote_name, "remote", N_("remote name")),
		OPT_BOOL(0, "all", &send_all, N_("push all refs")),
		OPT_BOOL('n' , "dry-run", &dry_run, N_("dry run")),
		OPT_BOOL(0, "mirror", &send_mirror, N_("mirror all refs")),
		OPT_BOOL('f', "force", &force_update, N_("force updates")),
		{ OPTION_CALLBACK,
		  0, "signed", &push_cert, "yes|no|if-asked", N_("GPG sign the push"),
		  PARSE_OPT_OPTARG, option_parse_push_signed },
		OPT_BOOL(0, "progress", &progress, N_("force progress reporting")),
		OPT_BOOL(0, "thin", &use_thin_pack, N_("use thin pack")),
		OPT_BOOL(0, "atomic", &atomic, N_("request atomic transaction on remote side")),
		OPT_BOOL(0, "stateless-rpc", &stateless_rpc, N_("use stateless RPC protocol")),
		OPT_BOOL(0, "stdin", &from_stdin, N_("read refs from stdin")),
		OPT_BOOL(0, "helper-status", &helper_status, N_("print status from remote helper")),
		{ OPTION_CALLBACK,
		  0, CAS_OPT_NAME, &cas, N_("refname>:<expect"),
		  N_("require old value of ref to be at this value"),
		  PARSE_OPT_OPTARG, parseopt_push_cas_option },
		OPT_END()
	};

	git_config(send_pack_config, NULL);
	argc = parse_options(argc, argv, prefix, options, send_pack_usage, 0);
	if (argc > 0) {
		dest = argv[0];
		refspecs = (const char **)(argv + 1);
		nr_refspecs = argc - 1;
	}

	if (!dest)
		usage_with_options(send_pack_usage, options);

	args.verbose = verbose;
	args.dry_run = dry_run;
	args.send_mirror = send_mirror;
	args.force_update = force_update;
	args.quiet = quiet;
	args.push_cert = push_cert;
	args.progress = progress;
	args.use_thin_pack = use_thin_pack;
	args.atomic = atomic;
	args.stateless_rpc = stateless_rpc;

	if (from_stdin) {
		struct argv_array all_refspecs = ARGV_ARRAY_INIT;

		for (i = 0; i < nr_refspecs; i++)
			argv_array_push(&all_refspecs, refspecs[i]);

		if (args.stateless_rpc) {
			const char *buf;
			while ((buf = packet_read_line(0, NULL)))
				argv_array_push(&all_refspecs, buf);
		} else {
			struct strbuf line = STRBUF_INIT;
			while (strbuf_getline(&line, stdin) != EOF)
				argv_array_push(&all_refspecs, line.buf);
			strbuf_release(&line);
		}

		refspecs = all_refspecs.argv;
		nr_refspecs = all_refspecs.argc;
	}

	/*
	 * --all and --mirror are incompatible; neither makes sense
	 * with any refspecs.
	 */
	if ((nr_refspecs > 0 && (send_all || args.send_mirror)) ||
	    (send_all && args.send_mirror))
		usage_with_options(send_pack_usage, options);

	if (remote_name) {
		remote = remote_get(remote_name);
		if (!remote_has_url(remote, dest)) {
			die("Destination %s is not a uri for %s",
			    dest, remote_name);
		}
	}

	if (progress == -1)
		progress = !args.quiet && isatty(2);
	args.progress = progress;

	if (args.stateless_rpc) {
		conn = NULL;
		fd[0] = 0;
		fd[1] = 1;
	} else {
		conn = git_connect(fd, dest, receivepack,
			args.verbose ? CONNECT_VERBOSE : 0);
	}

	get_remote_heads(fd[0], NULL, 0, &remote_refs, REF_NORMAL,
			 &extra_have, &shallow);

	transport_verify_remote_names(nr_refspecs, refspecs);

	local_refs = get_local_heads();

	f