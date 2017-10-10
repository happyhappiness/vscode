 		OPT_RERERE_AUTOUPDATE(&opts->allow_rerere_auto),
 		OPT_STRING(0, "strategy", &opts->strategy, N_("strategy"), N_("merge strategy")),
 		OPT_CALLBACK('X', "strategy-option", &opts, N_("option"),
 			N_("option for merge strategy"), option_parse_x),
 		{ OPTION_STRING, 'S', "gpg-sign", &opts->gpg_sign, N_("key-id"),
 		  N_("GPG sign commit"), PARSE_OPT_OPTARG, NULL, (intptr_t) "" },
-		OPT_END(),
-		OPT_END(),
-		OPT_END(),
-		OPT_END(),
-		OPT_END(),
-		OPT_END(),
+		OPT_END()
 	};
+	struct option *options = base_options;
 
 	if (opts->action == REPLAY_PICK) {
 		struct option cp_extra[] = {
 			OPT_BOOL('x', NULL, &opts->record_origin, N_("append commit name")),
 			OPT_BOOL(0, "ff", &opts->allow_ff, N_("allow fast-forward")),
 			OPT_BOOL(0, "allow-empty", &opts->allow_empty, N_("preserve initially empty commits")),
 			OPT_BOOL(0, "allow-empty-message", &opts->allow_empty_message, N_("allow commits with empty messages")),
 			OPT_BOOL(0, "keep-redundant-commits", &opts->keep_redundant_commits, N_("keep redundant, empty commits")),
 			OPT_END(),
 		};
-		if (parse_options_concat(options, ARRAY_SIZE(options), cp_extra))
-			die(_("program error"));
+		options = parse_options_concat(options, cp_extra);
 	}
 
 	argc = parse_options(argc, argv, NULL, options, usage_str,
 			PARSE_OPT_KEEP_ARGV0 |
 			PARSE_OPT_KEEP_UNKNOWN);
 
