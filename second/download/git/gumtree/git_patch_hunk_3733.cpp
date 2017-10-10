 			if (!DIFF_FILE_VALID(p->two))
 				continue; /* unmerged */
 			else if (options->single_follow &&
 				 strcmp(options->single_follow, p->two->path))
 				continue; /* not interested */
 			else if (!DIFF_OPT_TST(options, RENAME_EMPTY) &&
-				 is_empty_blob_sha1(p->two->sha1))
+				 is_empty_blob_sha1(p->two->oid.hash))
 				continue;
 			else if (add_rename_dst(p->two) < 0) {
 				warning("skipping rename detection, detected"
 					" duplicate destination '%s'",
 					p->two->path);
 				goto cleanup;
 			}
 		}
 		else if (!DIFF_OPT_TST(options, RENAME_EMPTY) &&
-			 is_empty_blob_sha1(p->one->sha1))
+			 is_empty_blob_sha1(p->one->oid.hash))
 			continue;
 		else if (!DIFF_PAIR_UNMERGED(p) && !DIFF_FILE_VALID(p->two)) {
 			/*
 			 * If the source is a broken "delete", and
 			 * they did not really want to get broken,
 			 * that means the source actually stays.
