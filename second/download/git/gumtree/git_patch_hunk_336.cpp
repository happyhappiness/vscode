 	git_config(git_cat_file_config, NULL);
 
 	batch.buffer_output = -1;
 	argc = parse_options(argc, argv, prefix, options, cat_file_usage, 0);
 
 	if (opt) {
-		if (argc == 1)
+		if (batch.enabled && (opt == 'c' || opt == 'w'))
+			batch.cmdmode = opt;
+		else if (argc == 1)
 			obj_name = argv[0];
 		else
 			usage_with_options(cat_file_usage, options);
 	}
 	if (!opt && !batch.enabled) {
 		if (argc == 2) {
 			exp_type = argv[0];
 			obj_name = argv[1];
 		} else
 			usage_with_options(cat_file_usage, options);
 	}
-	if (batch.enabled && (opt || argc)) {
-		usage_with_options(cat_file_usage, options);
+	if (batch.enabled) {
+		if (batch.cmdmode != opt || argc)
+			usage_with_options(cat_file_usage, options);
+		if (batch.cmdmode && batch.all_objects)
+			die("--batch-all-objects cannot be combined with "
+			    "--textconv nor with --filters");
 	}
 
 	if ((batch.follow_symlinks || batch.all_objects) && !batch.enabled) {
 		usage_with_options(cat_file_usage, options);
 	}
 
+	if (force_path && opt != 'c' && opt != 'w') {
+		error("--path=<path> needs --textconv or --filters");
+		usage_with_options(cat_file_usage, options);
+	}
+
+	if (force_path && batch.enabled) {
+		error("--path=<path> incompatible with --batch");
+		usage_with_options(cat_file_usage, options);
+	}
+
 	if (batch.buffer_output < 0)
 		batch.buffer_output = batch.all_objects;
 
 	if (batch.enabled)
 		return batch_objects(&batch);
 
