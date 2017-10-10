 		 * run diff_flush_patch for the exit status. setting
 		 * options->file to /dev/null should be safe, because we
 		 * aren't supposed to produce any output anyway.
 		 */
 		if (options->close_file)
 			fclose(options->file);
-		options->file = fopen("/dev/null", "w");
-		if (!options->file)
-			die_errno("Could not open /dev/null");
+		options->file = xfopen("/dev/null", "w");
 		options->close_file = 1;
 		for (i = 0; i < q->nr; i++) {
 			struct diff_filepair *p = q->queue[i];
 			if (check_pair_status(p))
 				diff_flush_patch(p, options);
 			if (options->found_changes)
