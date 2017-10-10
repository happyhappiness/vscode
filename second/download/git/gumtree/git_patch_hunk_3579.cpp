 		struct rev_info rev_info;
 		const char *diff_filter_str = "--diff-filter=AM";
 
 		init_revisions(&rev_info, NULL);
 		rev_info.diffopt.output_format = DIFF_FORMAT_NAME_STATUS;
 		diff_opt_parse(&rev_info.diffopt, &diff_filter_str, 1, rev_info.prefix);
-		add_pending_sha1(&rev_info, "HEAD", our_tree, 0);
+		add_pending_sha1(&rev_info, "HEAD", our_tree.hash, 0);
 		diff_setup_done(&rev_info.diffopt);
 		run_diff_index(&rev_info, 1);
 	}
 
 	if (run_apply(state, index_path))
 		return error(_("Did you hand edit your patch?\n"
 				"It does not apply to blobs recorded in its index."));
 
-	if (write_index_as_tree(their_tree, &the_index, index_path, 0, NULL))
+	if (write_index_as_tree(their_tree.hash, &the_index, index_path, 0, NULL))
 		return error("could not write tree");
 
 	say(state, stdout, _("Falling back to patching base and 3-way merge..."));
 
 	discard_cache();
 	read_cache();
