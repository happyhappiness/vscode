 		OPT_BOOL(0, "progress", &progress, N_("force progress reporting")),
 		OPT_BIT(0, "prune", &flags, N_("prune locally removed refs"),
 			TRANSPORT_PUSH_PRUNE),
 		OPT_BIT(0, "no-verify", &flags, N_("bypass pre-push hook"), TRANSPORT_PUSH_NO_HOOK),
 		OPT_BIT(0, "follow-tags", &flags, N_("push missing but relevant tags"),
 			TRANSPORT_PUSH_FOLLOW_TAGS),
-		OPT_BIT(0, "signed", &flags, N_("GPG sign the push"), TRANSPORT_PUSH_CERT),
+		{ OPTION_CALLBACK,
+		  0, "signed", &push_cert, "yes|no|if-asked", N_("GPG sign the push"),
+		  PARSE_OPT_OPTARG, option_parse_push_signed },
 		OPT_BIT(0, "atomic", &flags, N_("request atomic transaction on remote side"), TRANSPORT_PUSH_ATOMIC),
 		OPT_END()
 	};
 
 	packet_trace_identity("push");
 	git_config(git_push_config, &flags);
 	argc = parse_options(argc, argv, prefix, options, push_usage, 0);
+	set_push_cert_flags(&flags, push_cert);
 
 	if (deleterefs && (tags || (flags & (TRANSPORT_PUSH_ALL | TRANSPORT_PUSH_MIRROR))))
 		die(_("--delete is incompatible with --all, --mirror and --tags"));
 	if (deleterefs && argc < 2)
 		die(_("--delete doesn't make sense without any refs"));
 
