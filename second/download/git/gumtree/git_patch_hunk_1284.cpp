 	if (list.nr || cached || show_in_pager)
 		num_threads = 0;
 	else if (num_threads == 0)
 		num_threads = GREP_NUM_THREADS_DEFAULT;
 	else if (num_threads < 0)
 		die(_("invalid number of threads specified (%d)"), num_threads);
+	if (num_threads == 1)
+		num_threads = 0;
 #else
+	if (num_threads)
+		warning(_("no threads support, ignoring --threads"));
 	num_threads = 0;
 #endif
 
+	if (!num_threads)
+		/*
+		 * The compiled patterns on the main path are only
+		 * used when not using threading. Otherwise
+		 * start_threads() below calls compile_grep_patterns()
+		 * for each thread.
+		 */
+		compile_grep_patterns(&opt);
+
 #ifndef NO_PTHREADS
 	if (num_threads) {
 		if (!(opt.name_only || opt.unmatch_name_only || opt.count)
 		    && (opt.pre_context || opt.post_context ||
 			opt.file_break || opt.funcbody))
 			skip_first_line = 1;
