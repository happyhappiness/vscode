int cmd_push(int argc, const char **argv, const char *prefix)
{
	int flags = 0;
	int tags = 0;
	int push_cert = -1;
	int rc;
	const char *repo = NULL;	/* default repository */
	static struct string_list push_options = STRING_LIST_INIT_DUP;
	static struct string_list_item *item;

	struct option options[] = {
		OPT__VERBOSITY(&verbosity),
		OPT_STRING( 0 , "repo", &repo, N_("repository"), N_("repository")),
		OPT_BIT( 0 , "all", &flags, N_("push all refs"), TRANSPORT_PUSH_ALL),
		OPT_BIT( 0 , "mirror", &flags, N_("mirror all refs"),
			    (TRANSPORT_PUSH_MIRROR|TRANSPORT_PUSH_FORCE)),
		OPT_BOOL('d', "delete", &deleterefs, N_("delete refs")),
		OPT_BOOL( 0 , "tags", &tags, N_("push tags (can't be used with --all or --mirror)")),
		OPT_BIT('n' , "dry-run", &flags, N_("dry run"), TRANSPORT_PUSH_DRY_RUN),
		OPT_BIT( 0,  "porcelain", &flags, N_("machine-readable output"), TRANSPORT_PUSH_PORCELAIN),
		OPT_BIT('f', "force", &flags, N_("force updates"), TRANSPORT_PUSH_FORCE),
		{ OPTION_CALLBACK,
		  0, CAS_OPT_NAME, &cas, N_("refname>:<expect"),
		  N_("require old value of ref to be at this value"),
		  PARSE_OPT_OPTARG, parseopt_push_cas_option },
		{ OPTION_CALLBACK, 0, "recurse-submodules", &recurse_submodules, "check|on-demand|no",
			N_("control recursive pushing of submodules"),
			PARSE_OPT_OPTARG, option_parse_recurse_submodules },
		OPT_BOOL( 0 , "thin", &thin, N_("use thin pack")),
		OPT_STRING( 0 , "receive-pack", &receivepack, "receive-pack", N_("receive pack program")),
		OPT_STRING( 0 , "exec", &receivepack, "receive-pack", N_("receive pack program")),
		OPT_BIT('u', "set-upstream", &flags, N_("set upstream for git pull/status"),
			TRANSPORT_PUSH_SET_UPSTREAM),
		OPT_BOOL(0, "progress", &progress, N_("force progress reporting")),
		OPT_BIT(0, "prune", &flags, N_("prune locally removed refs"),
			TRANSPORT_PUSH_PRUNE),
		OPT_BIT(0, "no-verify", &flags, N_("bypass pre-push hook"), TRANSPORT_PUSH_NO_HOOK),
		OPT_BIT(0, "follow-tags", &flags, N_("push missing but relevant tags"),
			TRANSPORT_PUSH_FOLLOW_TAGS),
		{ OPTION_CALLBACK,
		  0, "signed", &push_cert, "yes|no|if-asked", N_("GPG sign the push"),
		  PARSE_OPT_OPTARG, option_parse_push_signed },
		OPT_BIT(0, "atomic", &flags, N_("request atomic transaction on remote side"), TRANSPORT_PUSH_ATOMIC),
		OPT_STRING_LIST('o', "push-option", &push_options, N_("server-specific"), N_("option to transmit")),
		OPT_SET_INT('4', "ipv4", &family, N_("use IPv4 addresses only"),
				TRANSPORT_FAMILY_IPV4),
		OPT_SET_INT('6', "ipv6", &family, N_("use IPv6 addresses only"),
				TRANSPORT_FAMILY_IPV6),
		OPT_END()
	};

	packet_trace_identity("push");
	git_config(git_push_config, &flags);
	argc = parse_options(argc, argv, prefix, options, push_usage, 0);
	set_push_cert_flags(&flags, push_cert);

	if (deleterefs && (tags || (flags & (TRANSPORT_PUSH_ALL | TRANSPORT_PUSH_MIRROR))))
		die(_("--delete is incompatible with --all, --mirror and --tags"));
	if (deleterefs && argc < 2)
		die(_("--delete doesn't make sense without any refs"));

	if (recurse_submodules == RECURSE_SUBMODULES_CHECK)
		flags |= TRANSPORT_RECURSE_SUBMODULES_CHECK;
	else if (recurse_submodules == RECURSE_SUBMODULES_ON_DEMAND)
		flags |= TRANSPORT_RECURSE_SUBMODULES_ON_DEMAND;

	if (tags)
		add_refspec("refs/tags/*");

	if (argc > 0) {
		repo = argv[0];
		set_refspecs(argv + 1, argc - 1, repo);
	}

	for_each_string_list_item(item, &push_options)
		if (strchr(item->string, '\n'))
			die(_("push options must not have new line characters"));

	rc = do_push(repo, flags, &push_options);
	if (rc == -1)
		usage_with_options(push_usage, options);
	else
		return rc;
}