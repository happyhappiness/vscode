 		else
 			allow_unadvertised_object_request &= ~ALLOW_REACHABLE_SHA1;
 	} else if (!strcmp("uploadpack.keepalive", var)) {
 		keepalive = git_config_int(var, value);
 		if (!keepalive)
 			keepalive = -1;
+	} else if (current_config_scope() != CONFIG_SCOPE_REPO) {
+		if (!strcmp("uploadpack.packobjectshook", var))
+			return git_config_string(&pack_objects_hook, var, value);
 	}
 	return parse_hide_refs_config(var, value, "uploadpack");
 }
 
 int cmd_main(int argc, const char **argv)
 {
 	const char *dir;
-	int i;
 	int strict = 0;
+	struct option options[] = {
+		OPT_BOOL(0, "stateless-rpc", &stateless_rpc,
+			 N_("quit after a single request/response exchange")),
+		OPT_BOOL(0, "advertise-refs", &advertise_refs,
+			 N_("exit immediately after initial ref advertisement")),
+		OPT_BOOL(0, "strict", &strict,
+			 N_("do not try <directory>/.git/ if <directory> is no Git directory")),
+		OPT_INTEGER(0, "timeout", &timeout,
+			    N_("interrupt transfer after <n> seconds of inactivity")),
+		OPT_END()
+	};
 
 	packet_trace_identity("upload-pack");
 	check_replace_refs = 0;
 
-	for (i = 1; i < argc; i++) {
-		const char *arg = argv[i];
+	argc = parse_options(argc, argv, NULL, options, upload_pack_usage, 0);
 
-		if (arg[0] != '-')
-			break;
-		if (!strcmp(arg, "--advertise-refs")) {
-			advertise_refs = 1;
-			continue;
-		}
-		if (!strcmp(arg, "--stateless-rpc")) {
-			stateless_rpc = 1;
-			continue;
-		}
-		if (!strcmp(arg, "--strict")) {
-			strict = 1;
-			continue;
-		}
-		if (starts_with(arg, "--timeout=")) {
-			timeout = atoi(arg+10);
-			daemon_mode = 1;
-			continue;
-		}
-		if (!strcmp(arg, "--")) {
-			i++;
-			break;
-		}
-	}
+	if (argc != 1)
+		usage_with_options(upload_pack_usage, options);
 
-	if (i != argc-1)
-		usage(upload_pack_usage);
+	if (timeout)
+		daemon_mode = 1;
 
 	setup_path();
 
-	dir = argv[i];
+	dir = argv[0];
 
 	if (!enter_repo(dir, strict))
 		die("'%s' does not appear to be a git repository", dir);
 
 	git_config(upload_pack_config, NULL);
 	upload_pack();
