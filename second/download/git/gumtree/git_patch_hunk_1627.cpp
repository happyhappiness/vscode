 		die(_("--points-at option is only allowed in list mode"));
 	if (filter.merge_commit)
 		die(_("--merged and --no-merged options are only allowed in list mode"));
 	if (cmdmode == 'd')
 		return for_each_tag_name(argv, delete_tag, NULL);
 	if (cmdmode == 'v') {
-		if (format)
-			verify_ref_format(format);
-		return for_each_tag_name(argv, verify_tag, format);
+		if (format.format && verify_ref_format(&format))
+			usage_with_options(git_tag_usage, options);
+		return for_each_tag_name(argv, verify_tag, &format);
 	}
 
 	if (msg.given || msgfile) {
 		if (msg.given && msgfile)
 			die(_("only one -F or -m option is allowed."));
 		if (msg.given)
