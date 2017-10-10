 	if (queue_diff(&revs->diffopt, paths[0], paths[1]))
 		exit(1);
 	diff_set_mnemonic_prefix(&revs->diffopt, "1/", "2/");
 	diffcore_std(&revs->diffopt);
 	diff_flush(&revs->diffopt);
 
-	strbuf_release(&replacement);
-
 	/*
 	 * The return code for --no-index imitates diff(1):
 	 * 0 = no changes, 1 = changes, else error
 	 */
 	exit(diff_result_code(&revs->diffopt, 0));
 }
