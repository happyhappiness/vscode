 		die("internal error in merge #3");
 	if (!DIFF_FILE_VALID(c->two))
 		die("internal error in merge #4");
 
 	dp = diff_queue(outq, d->one, c->two);
 	dp->score = p->score;
+	/*
+	 * We will be one extra user of the same src side of the
+	 * broken pair, if it was used as the rename source for other
+	 * paths elsewhere.  Increment to mark that the path stays
+	 * in the resulting tree.
+	 */
+	d->one->rename_used++;
 	diff_free_filespec_data(d->two);
 	diff_free_filespec_data(c->one);
 	free(d);
 	free(c);
 }
 
