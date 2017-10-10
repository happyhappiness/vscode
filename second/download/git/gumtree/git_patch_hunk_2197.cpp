 		 * We should exit here only if the "bad"
 		 * commit is also a "skip" commit.
 		 */
 		exit_if_skipped_commits(tried, NULL);
 
 		printf("%s was both good and bad\n",
-		       sha1_to_hex(current_bad_sha1));
+		       oid_to_hex(current_bad_oid));
 		exit(1);
 	}
 
 	if (!all) {
 		fprintf(stderr, "No testable commit found.\n"
 			"Maybe you started with bad path parameters?\n");
 		exit(4);
 	}
 
 	bisect_rev = revs.commits->item->object.sha1;
-	memcpy(bisect_rev_hex, sha1_to_hex(bisect_rev), 41);
+	memcpy(bisect_rev_hex, sha1_to_hex(bisect_rev), GIT_SHA1_HEXSZ + 1);
 
-	if (!hashcmp(bisect_rev, current_bad_sha1)) {
-		exit_if_skipped_commits(tried, current_bad_sha1);
+	if (!hashcmp(bisect_rev, current_bad_oid->hash)) {
+		exit_if_skipped_commits(tried, current_bad_oid);
 		printf("%s is the first bad commit\n", bisect_rev_hex);
 		show_diff_tree(prefix, revs.commits->item);
 		/* This means the bisection process succeeded. */
 		exit(10);
 	}
 
