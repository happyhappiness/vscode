 	 * from reflog if the repository was pruned with older git.
 	 */
 	if (cb.stalefix) {
 		init_revisions(&cb.revs, prefix);
 		if (cb.verbose)
 			printf("Marking reachable objects...");
-		mark_reachable_objects(&cb.revs, 0, NULL);
+		mark_reachable_objects(&cb.revs, 0, 0, NULL);
 		if (cb.verbose)
 			putchar('\n');
 	}
 
 	if (do_all) {
 		struct collect_reflog_cb collected;
