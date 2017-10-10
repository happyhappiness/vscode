 		struct rev_info rev_info;
 		const char *diff_filter_str = "--diff-filter=AM";
 
 		init_revisions(&rev_info, NULL);
 		rev_info.diffopt.output_format = DIFF_FORMAT_NAME_STATUS;
 		diff_opt_parse(&rev_info.diffopt, &diff_filter_str, 1, rev_info.prefix);
-		add_pending_sha1(&rev_info, "HEAD", our_tree.hash, 0);
+		add_pending_oid(&rev_info, "HEAD", &our_tree, 0);
 		diff_setup_done(&rev_info.diffopt);
 		run_diff_index(&rev_info, 1);
 	}
 
 	if (run_apply(state, index_path))
 		return error(_("Did you hand edit your patch?\n"
