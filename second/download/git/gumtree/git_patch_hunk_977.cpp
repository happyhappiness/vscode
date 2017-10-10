 
 	printf("%s", ret);
 	strbuf_release(&sb);
 	return 0;
 }
 
+static int push_check(int argc, const char **argv, const char *prefix)
+{
+	struct remote *remote;
+
+	if (argc < 2)
+		die("submodule--helper push-check requires at least 1 argument");
+
+	/*
+	 * The remote must be configured.
+	 * This is to avoid pushing to the exact same URL as the parent.
+	 */
+	remote = pushremote_get(argv[1]);
+	if (!remote || remote->origin == REMOTE_UNCONFIGURED)
+		die("remote '%s' not configured", argv[1]);
+
+	/* Check the refspec */
+	if (argc > 2) {
+		int i, refspec_nr = argc - 2;
+		struct ref *local_refs = get_local_heads();
+		struct refspec *refspec = parse_push_refspec(refspec_nr,
+							     argv + 2);
+
+		for (i = 0; i < refspec_nr; i++) {
+			struct refspec *rs = refspec + i;
+
+			if (rs->pattern || rs->matching)
+				continue;
+
+			/*
+			 * LHS must match a single ref
+			 * NEEDSWORK: add logic to special case 'HEAD' once
+			 * working with submodules in a detached head state
+			 * ceases to be the norm.
+			 */
+			if (count_refspec_match(rs->src, local_refs, NULL) != 1)
+				die("src refspec '%s' must name a ref",
+				    rs->src);
+		}
+		free_refspec(refspec_nr, refspec);
+	}
+
+	return 0;
+}
+
 static int absorb_git_dirs(int argc, const char **argv, const char *prefix)
 {
 	int i;
 	struct pathspec pathspec;
 	struct module_list list = MODULE_LIST_INIT;
 	unsigned flags = ABSORB_GITDIR_RECURSE_SUBMODULES;
