 		 * one branch which doesn't exist locally, but is the
 		 * name of a remote-tracking branch.
 		 */
 		if (argc == 1 && track == BRANCH_TRACK_OVERRIDE &&
 		    !branch_existed && remote_tracking) {
 			fprintf(stderr, _("\nIf you wanted to make '%s' track '%s', do this:\n\n"), head, branch->name);
-			fprintf(stderr, _("    git branch -d %s\n"), branch->name);
-			fprintf(stderr, _("    git branch --set-upstream-to %s\n"), branch->name);
+			fprintf(stderr, "    git branch -d %s\n", branch->name);
+			fprintf(stderr, "    git branch --set-upstream-to %s\n", branch->name);
 		}
 
 	} else
 		usage_with_options(builtin_branch_usage, options);
 
 	return 0;
