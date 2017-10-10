 	int fd, ret = 0;
 
 	strbuf_addstr(&mtime_dir, "mtime-test-XXXXXX");
 	if (!mkdtemp(mtime_dir.buf))
 		die_errno("Could not make temporary directory");
 
-	fprintf(stderr, _("Testing "));
+	fprintf(stderr, _("Testing mtime in '%s' "), xgetcwd());
 	atexit(remove_test_directory);
 	xstat_mtime_dir(&st);
 	fill_stat_data(&base, &st);
 	fputc('.', stderr);
 
 	avoid_racy();
