 	}
 	return 0;
 }
 
 int cmd_ls_remote(int argc, const char **argv, const char *prefix)
 {
-	int i;
 	const char *dest = NULL;
 	unsigned flags = 0;
 	int get_url = 0;
 	int quiet = 0;
 	int status = 0;
+	int show_symref_target = 0;
 	const char *uploadpack = NULL;
 	const char **pattern = NULL;
 
 	struct remote *remote;
 	struct transport *transport;
 	const struct ref *ref;
 
-	if (argc == 2 && !strcmp("-h", argv[1]))
-		usage(ls_remote_usage);
-
-	for (i = 1; i < argc; i++) {
-		const char *arg = argv[i];
-
-		if (*arg == '-') {
-			if (starts_with(arg, "--upload-pack=")) {
-				uploadpack = arg + 14;
-				continue;
-			}
-			if (starts_with(arg, "--exec=")) {
-				uploadpack = arg + 7;
-				continue;
-			}
-			if (!strcmp("--tags", arg) || !strcmp("-t", arg)) {
-				flags |= REF_TAGS;
-				continue;
-			}
-			if (!strcmp("--heads", arg) || !strcmp("-h", arg)) {
-				flags |= REF_HEADS;
-				continue;
-			}
-			if (!strcmp("--refs", arg)) {
-				flags |= REF_NORMAL;
-				continue;
-			}
-			if (!strcmp("--quiet", arg) || !strcmp("-q", arg)) {
-				quiet = 1;
-				continue;
-			}
-			if (!strcmp("--get-url", arg)) {
-				get_url = 1;
-				continue;
-			}
-			if (!strcmp("--exit-code", arg)) {
-				/* return this code if no refs are reported */
-				status = 2;
-				continue;
-			}
-			usage(ls_remote_usage);
-		}
-		dest = arg;
-		i++;
-		break;
+	struct option options[] = {
+		OPT__QUIET(&quiet, N_("do not print remote URL")),
+		OPT_STRING(0, "upload-pack", &uploadpack, N_("exec"),
+			   N_("path of git-upload-pack on the remote host")),
+		{ OPTION_STRING, 0, "exec", &uploadpack, N_("exec"),
+			   N_("path of git-upload-pack on the remote host"),
+			   PARSE_OPT_HIDDEN },
+		OPT_BIT('t', "tags", &flags, N_("limit to tags"), REF_TAGS),
+		OPT_BIT('h', "heads", &flags, N_("limit to heads"), REF_HEADS),
+		OPT_BIT(0, "refs", &flags, N_("do not show peeled tags"), REF_NORMAL),
+		OPT_BOOL(0, "get-url", &get_url,
+			 N_("take url.<base>.insteadOf into account")),
+		OPT_SET_INT(0, "exit-code", &status,
+			    N_("exit with exit code 2 if no matching refs are found"), 2),
+		OPT_BOOL(0, "symref", &show_symref_target,
+			 N_("show underlying ref in addition to the object pointed by it")),
+		OPT_END()
+	};
+
+	argc = parse_options(argc, argv, prefix, options, ls_remote_usage,
+			     PARSE_OPT_STOP_AT_NON_OPTION);
+	dest = argv[0];
+
+	if (argc > 1) {
+		int i;
+		pattern = xcalloc(argc, sizeof(const char *));
+		for (i = 1; i < argc; i++)
+			pattern[i - 1] = xstrfmt("*/%s", argv[i]);
 	}
 
-	if (argv[i]) {
-		int j;
-		pattern = xcalloc(argc - i + 1, sizeof(const char *));
-		for (j = i; j < argc; j++)
-			pattern[j - i] = xstrfmt("*/%s", argv[j]);
-	}
 	remote = remote_get(dest);
 	if (!remote) {
 		if (dest)
 			die("bad repository '%s'", dest);
 		die("No remote configured to list refs from.");
 	}
