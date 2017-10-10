 			seen_dashdash = 1;
 		}
 		break;
 	}
 
 #ifndef NO_PTHREADS
-	if (list.nr || cached || online_cpus() == 1)
-		use_threads = 0;
+	if (list.nr || cached || show_in_pager)
+		num_threads = 0;
+	else if (num_threads == 0)
+		num_threads = GREP_NUM_THREADS_DEFAULT;
+	else if (num_threads < 0)
+		die(_("invalid number of threads specified (%d)"), num_threads);
 #else
-	use_threads = 0;
+	num_threads = 0;
 #endif
 
 #ifndef NO_PTHREADS
-	if (use_threads) {
+	if (num_threads) {
 		if (!(opt.name_only || opt.unmatch_name_only || opt.count)
 		    && (opt.pre_context || opt.post_context ||
 			opt.file_break || opt.funcbody))
 			skip_first_line = 1;
 		start_threads(&opt);
 	}
