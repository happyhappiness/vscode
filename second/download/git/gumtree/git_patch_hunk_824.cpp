 				continue;
 			}
 			if (!strcmp(arg, "--symbolic-full-name")) {
 				symbolic = SHOW_SYMBOLIC_FULL;
 				continue;
 			}
-			if (starts_with(arg, "--abbrev-ref") &&
-			    (!arg[12] || arg[12] == '=')) {
+			if (opt_with_value(arg, "--abbrev-ref", &arg)) {
 				abbrev_ref = 1;
 				abbrev_ref_strict = warn_ambiguous_refs;
-				if (arg[12] == '=') {
-					if (!strcmp(arg + 13, "strict"))
+				if (arg) {
+					if (!strcmp(arg, "strict"))
 						abbrev_ref_strict = 1;
-					else if (!strcmp(arg + 13, "loose"))
+					else if (!strcmp(arg, "loose"))
 						abbrev_ref_strict = 0;
 					else
-						die("unknown mode for %s", arg);
+						die("unknown mode for --abbrev-ref: %s",
+						    arg);
 				}
 				continue;
 			}
 			if (!strcmp(arg, "--all")) {
 				for_each_ref(show_reference, NULL);
 				continue;
 			}
-			if (starts_with(arg, "--disambiguate=")) {
-				for_each_abbrev(arg + 15, show_abbrev, NULL);
+			if (skip_prefix(arg, "--disambiguate=", &arg)) {
+				for_each_abbrev(arg, show_abbrev, NULL);
 				continue;
 			}
 			if (!strcmp(arg, "--bisect")) {
 				for_each_ref_in("refs/bisect/bad", show_reference, NULL);
 				for_each_ref_in("refs/bisect/good", anti_reference, NULL);
 				continue;
 			}
-			if (starts_with(arg, "--branches=")) {
-				for_each_glob_ref_in(show_reference, arg + 11,
-					"refs/heads/", NULL);
-				clear_ref_exclusion(&ref_excludes);
-				continue;
-			}
-			if (!strcmp(arg, "--branches")) {
-				for_each_branch_ref(show_reference, NULL);
-				clear_ref_exclusion(&ref_excludes);
-				continue;
-			}
-			if (starts_with(arg, "--tags=")) {
-				for_each_glob_ref_in(show_reference, arg + 7,
-					"refs/tags/", NULL);
-				clear_ref_exclusion(&ref_excludes);
-				continue;
-			}
-			if (!strcmp(arg, "--tags")) {
-				for_each_tag_ref(show_reference, NULL);
-				clear_ref_exclusion(&ref_excludes);
+			if (opt_with_value(arg, "--branches", &arg)) {
+				handle_ref_opt(arg, "refs/heads/");
 				continue;
 			}
-			if (starts_with(arg, "--glob=")) {
-				for_each_glob_ref(show_reference, arg + 7, NULL);
-				clear_ref_exclusion(&ref_excludes);
+			if (opt_with_value(arg, "--tags", &arg)) {
+				handle_ref_opt(arg, "refs/tags/");
 				continue;
 			}
-			if (starts_with(arg, "--remotes=")) {
-				for_each_glob_ref_in(show_reference, arg + 10,
-					"refs/remotes/", NULL);
-				clear_ref_exclusion(&ref_excludes);
+			if (skip_prefix(arg, "--glob=", &arg)) {
+				handle_ref_opt(arg, NULL);
 				continue;
 			}
-			if (!strcmp(arg, "--remotes")) {
-				for_each_remote_ref(show_reference, NULL);
-				clear_ref_exclusion(&ref_excludes);
+			if (opt_with_value(arg, "--remotes", &arg)) {
+				handle_ref_opt(arg, "refs/remotes/");
 				continue;
 			}
-			if (starts_with(arg, "--exclude=")) {
-				add_ref_exclusion(&ref_excludes, arg + 10);
+			if (skip_prefix(arg, "--exclude=", &arg)) {
+				add_ref_exclusion(&ref_excludes, arg);
 				continue;
 			}
 			if (!strcmp(arg, "--show-toplevel")) {
 				const char *work_tree = get_git_work_tree();
 				if (work_tree)
 					puts(work_tree);
