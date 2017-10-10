 		 * but first the most common case of merging one remote.
 		 */
 		finish_up_to_date("Already up-to-date.");
 		goto done;
 	} else if (fast_forward != FF_NO && !remoteheads->next &&
 			!common->next &&
-			!hashcmp(common->item->object.sha1, head_commit->object.sha1)) {
+			!hashcmp(common->item->object.oid.hash, head_commit->object.oid.hash)) {
 		/* Again the most common case of merging one remote. */
 		struct strbuf msg = STRBUF_INIT;
 		struct commit *commit;
-		char hex[41];
 
-		strcpy(hex, find_unique_abbrev(head_commit->object.sha1, DEFAULT_ABBREV));
-
-		if (verbosity >= 0)
-			printf(_("Updating %s..%s\n"),
-				hex,
-				find_unique_abbrev(remoteheads->item->object.sha1,
-				DEFAULT_ABBREV));
+		if (verbosity >= 0) {
+			char from[GIT_SHA1_HEXSZ + 1], to[GIT_SHA1_HEXSZ + 1];
+			find_unique_abbrev_r(from, head_commit->object.oid.hash,
+					      DEFAULT_ABBREV);
+			find_unique_abbrev_r(to, remoteheads->item->object.oid.hash,
+					      DEFAULT_ABBREV);
+			printf(_("Updating %s..%s\n"), from, to);
+		}
 		strbuf_addstr(&msg, "Fast-forward");
 		if (have_message)
 			strbuf_addstr(&msg,
 				" (no commit created; -m option ignored)");
 		commit = remoteheads->item;
 		if (!commit) {
 			ret = 1;
 			goto done;
 		}
 
-		if (checkout_fast_forward(head_commit->object.sha1,
-					  commit->object.sha1,
+		if (checkout_fast_forward(head_commit->object.oid.hash,
+					  commit->object.oid.hash,
 					  overwrite_ignore)) {
 			ret = 1;
 			goto done;
 		}
 
-		finish(head_commit, remoteheads, commit->object.sha1, msg.buf);
+		finish(head_commit, remoteheads, commit->object.oid.hash, msg.buf);
 		drop_save();
 		goto done;
 	} else if (!remoteheads->next && common->next)
 		;
 		/*
 		 * We are not doing octopus and not fast-forward.  Need
