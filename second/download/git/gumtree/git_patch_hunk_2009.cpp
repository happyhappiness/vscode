 	head = lookup_commit_or_die(sha1, "HEAD");
 	if (get_sha1("MERGE_HEAD", sha1))
 		die("--merge without MERGE_HEAD?");
 	other = lookup_commit_or_die(sha1, "MERGE_HEAD");
 	add_pending_object(revs, &head->object, "HEAD");
 	add_pending_object(revs, &other->object, "MERGE_HEAD");
-	bases = get_merge_bases(head, other, 1);
+	bases = get_merge_bases(head, other);
 	add_rev_cmdline_list(revs, bases, REV_CMD_MERGE_BASE, UNINTERESTING | BOTTOM);
 	add_pending_commit_list(revs, bases, UNINTERESTING | BOTTOM);
 	free_commit_list(bases);
 	head->object.flags |= SYMMETRIC_LEFT;
 
 	if (!active_nr)
