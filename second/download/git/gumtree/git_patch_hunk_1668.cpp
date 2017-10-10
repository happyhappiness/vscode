 }
 
 static int write_tar_filter_archive(const struct archiver *ar,
 				    struct archiver_args *args)
 {
 	struct strbuf cmd = STRBUF_INIT;
-	struct child_process filter;
+	struct child_process filter = CHILD_PROCESS_INIT;
 	const char *argv[2];
 	int r;
 
 	if (!ar->data)
 		die("BUG: tar-filter archiver called with no filter defined");
 
 	strbuf_addstr(&cmd, ar->data);
 	if (args->compression_level >= 0)
 		strbuf_addf(&cmd, " -%d", args->compression_level);
 
-	memset(&filter, 0, sizeof(filter));
 	argv[0] = cmd.buf;
 	argv[1] = NULL;
 	filter.argv = argv;
 	filter.use_shell = 1;
 	filter.in = -1;
 
