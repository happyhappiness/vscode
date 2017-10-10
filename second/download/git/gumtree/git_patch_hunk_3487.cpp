 				printf(_("remove '%s'\n"), path);
 			break;
 		}
 	}
 }
 
-int add_files_to_cache(const char *prefix,
-		       const struct pathspec *pathspec, int flags)
+int add_files_to_cache(const char *prefix, const struct pathspec *pathspec,
+	int flags, int force_mode)
 {
 	struct update_callback_data data;
 	struct rev_info rev;
 
 	memset(&data, 0, sizeof(data));
 	data.flags = flags;
+	data.force_mode = force_mode;
 
 	init_revisions(&rev, prefix);
 	setup_revisions(0, NULL, &rev, NULL);
 	if (pathspec)
 		copy_pathspec(&rev.prune_data, pathspec);
 	rev.diffopt.output_format = DIFF_FORMAT_CALLBACK;
