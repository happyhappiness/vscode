 	argc = parse_options(argc, argv, prefix, options, git_tag_usage, 0);
 
 	if (keyid) {
 		opt.sign = 1;
 		set_signing_key(keyid);
 	}
-	if (opt.sign)
-		annotate = 1;
+	create_tag_object = (opt.sign || annotate || msg.given || msgfile);
+
 	if (argc == 0 && !cmdmode)
 		cmdmode = 'l';
 
-	if ((annotate || msg.given || msgfile || force) && (cmdmode != 0))
+	if ((create_tag_object || force) && (cmdmode != 0))
 		usage_with_options(git_tag_usage, options);
 
 	finalize_colopts(&colopts, -1);
 	if (cmdmode == 'l' && filter.lines != -1) {
 		if (explicitly_enable_column(colopts))
 			die(_("--column and -n are incompatible"));
