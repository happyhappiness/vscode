 	return 1;
 }
 
 int cmd_receive_pack(int argc, const char **argv, const char *prefix)
 {
 	int advertise_refs = 0;
-	int i;
 	struct command *commands;
 	struct sha1_array shallow = SHA1_ARRAY_INIT;
 	struct sha1_array ref = SHA1_ARRAY_INIT;
 	struct shallow_info si;
 
-	packet_trace_identity("receive-pack");
+	struct option options[] = {
+		OPT__QUIET(&quiet, N_("quiet")),
+		OPT_HIDDEN_BOOL(0, "stateless-rpc", &stateless_rpc, NULL),
+		OPT_HIDDEN_BOOL(0, "advertise-refs", &advertise_refs, NULL),
+		OPT_HIDDEN_BOOL(0, "reject-thin-pack-for-testing", &reject_thin, NULL),
+		OPT_END()
+	};
 
-	argv++;
-	for (i = 1; i < argc; i++) {
-		const char *arg = *argv++;
+	packet_trace_identity("receive-pack");
 
-		if (*arg == '-') {
-			if (!strcmp(arg, "--quiet")) {
-				quiet = 1;
-				continue;
-			}
+	argc = parse_options(argc, argv, prefix, options, receive_pack_usage, 0);
 
-			if (!strcmp(arg, "--advertise-refs")) {
-				advertise_refs = 1;
-				continue;
-			}
-			if (!strcmp(arg, "--stateless-rpc")) {
-				stateless_rpc = 1;
-				continue;
-			}
-			if (!strcmp(arg, "--reject-thin-pack-for-testing")) {
-				fix_thin = 0;
-				continue;
-			}
+	if (argc > 1)
+		usage_msg_opt(_("Too many arguments."), receive_pack_usage, options);
+	if (argc == 0)
+		usage_msg_opt(_("You must specify a directory."), receive_pack_usage, options);
 
-			usage(receive_pack_usage);
-		}
-		if (service_dir)
-			usage(receive_pack_usage);
-		service_dir = arg;
-	}
-	if (!service_dir)
-		usage(receive_pack_usage);
+	service_dir = argv[0];
 
 	setup_path();
 
 	if (!enter_repo(service_dir, 0))
 		die("'%s' does not appear to be a git repository", service_dir);
 
