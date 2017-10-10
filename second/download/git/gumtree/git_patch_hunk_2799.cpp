 	if (get_sha1(arg, sha1))
 		die(_("Not a valid object name %s"), arg);
 	cmit = lookup_commit_reference(sha1);
 	if (!cmit)
 		die(_("%s is not a valid '%s' object"), arg, commit_type);
 
-	n = find_commit_name(cmit->object.sha1);
+	n = find_commit_name(cmit->object.oid.hash);
 	if (n && (tags || all || n->prio == 2)) {
 		/*
 		 * Exact match to an existing ref.
 		 */
 		display_name(n);
 		if (longformat)
-			show_suffix(0, n->tag ? n->tag->tagged->sha1 : sha1);
+			show_suffix(0, n->tag ? n->tag->tagged->oid.hash : sha1);
 		if (dirty)
 			printf("%s", dirty);
 		printf("\n");
 		return;
 	}
 
 	if (!max_candidates)
-		die(_("no tag exactly matches '%s'"), sha1_to_hex(cmit->object.sha1));
+		die(_("no tag exactly matches '%s'"), oid_to_hex(&cmit->object.oid));
 	if (debug)
 		fprintf(stderr, _("searching to describe %s\n"), arg);
 
 	if (!have_util) {
 		struct hashmap_iter iter;
 		struct commit *c;
