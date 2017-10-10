 
 	nr = all - reaches - 1;
 	steps = estimate_bisect_steps(all);
 
 	steps_msg = xstrfmt(Q_("(roughly %d step)", "(roughly %d steps)",
 		  steps), steps);
-	/* TRANSLATORS: the last %s will be replaced with
-	   "(roughly %d steps)" translation */
+	/*
+	 * TRANSLATORS: the last %s will be replaced with "(roughly %d
+	 * steps)" translation.
+	 */
 	printf(Q_("Bisecting: %d revision left to test after this %s\n",
 		  "Bisecting: %d revisions left to test after this %s\n",
 		  nr), nr, steps_msg);
 	free(steps_msg);
 
 	return bisect_checkout(bisect_rev, no_checkout);
