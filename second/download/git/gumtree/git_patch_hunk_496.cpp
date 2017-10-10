 {
 	const char *lref = o->local_ref ? o->local_ref : "local version";
 	const char *rref = o->remote_ref ? o->remote_ref : "remote version";
 
 	trace_printf("\t\t\tmerge_one_change_manual(obj = %.7s, base = %.7s, "
 	       "local = %.7s, remote = %.7s)\n",
-	       sha1_to_hex(p->obj), sha1_to_hex(p->base),
-	       sha1_to_hex(p->local), sha1_to_hex(p->remote));
+	       oid_to_hex(&p->obj), oid_to_hex(&p->base),
+	       oid_to_hex(&p->local), oid_to_hex(&p->remote));
 
 	/* add "Conflicts:" section to commit message first time through */
 	if (!o->has_worktree)
 		strbuf_addstr(&(o->commit_msg), "\n\nConflicts:\n");
 
-	strbuf_addf(&(o->commit_msg), "\t%s\n", sha1_to_hex(p->obj));
+	strbuf_addf(&(o->commit_msg), "\t%s\n", oid_to_hex(&p->obj));
 
 	if (o->verbosity >= 2)
-		printf("Auto-merging notes for %s\n", sha1_to_hex(p->obj));
+		printf("Auto-merging notes for %s\n", oid_to_hex(&p->obj));
 	check_notes_merge_worktree(o);
-	if (is_null_sha1(p->local)) {
+	if (is_null_oid(&p->local)) {
 		/* D/F conflict, checkout p->remote */
-		assert(!is_null_sha1(p->remote));
+		assert(!is_null_oid(&p->remote));
 		if (o->verbosity >= 1)
 			printf("CONFLICT (delete/modify): Notes for object %s "
 				"deleted in %s and modified in %s. Version from %s "
 				"left in tree.\n",
-				sha1_to_hex(p->obj), lref, rref, rref);
-		write_note_to_worktree(p->obj, p->remote);
-	} else if (is_null_sha1(p->remote)) {
+				oid_to_hex(&p->obj), lref, rref, rref);
+		write_note_to_worktree(p->obj.hash, p->remote.hash);
+	} else if (is_null_oid(&p->remote)) {
 		/* D/F conflict, checkout p->local */
-		assert(!is_null_sha1(p->local));
+		assert(!is_null_oid(&p->local));
 		if (o->verbosity >= 1)
 			printf("CONFLICT (delete/modify): Notes for object %s "
 				"deleted in %s and modified in %s. Version from %s "
 				"left in tree.\n",
-				sha1_to_hex(p->obj), rref, lref, lref);
-		write_note_to_worktree(p->obj, p->local);
+				oid_to_hex(&p->obj), rref, lref, lref);
+		write_note_to_worktree(p->obj.hash, p->local.hash);
 	} else {
 		/* "regular" conflict, checkout result of ll_merge() */
 		const char *reason = "content";
-		if (is_null_sha1(p->base))
+		if (is_null_oid(&p->base))
 			reason = "add/add";
-		assert(!is_null_sha1(p->local));
-		assert(!is_null_sha1(p->remote));
+		assert(!is_null_oid(&p->local));
+		assert(!is_null_oid(&p->remote));
 		if (o->verbosity >= 1)
 			printf("CONFLICT (%s): Merge conflict in notes for "
-				"object %s\n", reason, sha1_to_hex(p->obj));
+				"object %s\n", reason,
+				oid_to_hex(&p->obj));
 		ll_merge_in_worktree(o, p);
 	}
 
 	trace_printf("\t\t\tremoving from partial merge result\n");
-	remove_note(t, p->obj);
+	remove_note(t, p->obj.hash);
 
 	return 1;
 }
 
 static int merge_one_change(struct notes_merge_options *o,
 			    struct notes_merge_pair *p, struct notes_tree *t)
