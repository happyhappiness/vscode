 
 int cmd_upload_archive_writer(int argc, const char **argv, const char *prefix)
 {
 	struct argv_array sent_argv = ARGV_ARRAY_INIT;
 	const char *arg_cmd = "argument ";
 
-	if (argc != 2)
+	if (argc != 2 || !strcmp(argv[1], "-h"))
 		usage(upload_archive_usage);
 
 	if (!enter_repo(argv[1], 0))
 		die("'%s' does not appear to be a git repository", argv[1]);
 
 	/* put received options in sent_argv[] */
