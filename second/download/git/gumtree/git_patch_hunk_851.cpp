 	int rev_nr;
 	struct commit **rev = get_bad_and_good_commits(&rev_nr);
 
 	result = get_merge_bases_many(rev[0], rev_nr - 1, rev + 1);
 
 	for (; result; result = result->next) {
-		const unsigned char *mb = result->item->object.oid.hash;
-		if (!hashcmp(mb, current_bad_oid->hash)) {
+		const struct object_id *mb = &result->item->object.oid;
+		if (!oidcmp(mb, current_bad_oid)) {
 			handle_bad_merge_base();
-		} else if (0 <= sha1_array_lookup(&good_revs, mb)) {
+		} else if (0 <= oid_array_lookup(&good_revs, mb)) {
 			continue;
-		} else if (0 <= sha1_array_lookup(&skipped_revs, mb)) {
+		} else if (0 <= oid_array_lookup(&skipped_revs, mb)) {
 			handle_skipped_merge_base(mb);
 		} else {
 			printf(_("Bisecting: a merge base must be tested\n"));
-			exit(bisect_checkout(mb, no_checkout));
+			exit(bisect_checkout(mb->hash, no_checkout));
 		}
 	}
 
 	free(rev);
 	free_commit_list(result);
 }
