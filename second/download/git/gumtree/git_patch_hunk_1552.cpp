 		TODO_PICK : TODO_REVERT, cmit, opts, 0);
 }
 
 int sequencer_pick_revisions(struct replay_opts *opts)
 {
 	struct todo_list todo_list = TODO_LIST_INIT;
-	unsigned char sha1[20];
+	struct object_id oid;
 	int i, res;
 
 	assert(opts->revs);
 	if (read_and_refresh_cache(opts))
 		return -1;
 
 	for (i = 0; i < opts->revs->pending.nr; i++) {
-		unsigned char sha1[20];
+		struct object_id oid;
 		const char *name = opts->revs->pending.objects[i].name;
 
 		/* This happens when using --stdin. */
 		if (!strlen(name))
 			continue;
 
-		if (!get_sha1(name, sha1)) {
-			if (!lookup_commit_reference_gently(sha1, 1)) {
-				enum object_type type = sha1_object_info(sha1, NULL);
+		if (!get_oid(name, &oid)) {
+			if (!lookup_commit_reference_gently(&oid, 1)) {
+				enum object_type type = sha1_object_info(oid.hash, NULL);
 				return error(_("%s: can't cherry-pick a %s"),
 					name, typename(type));
 			}
 		} else
 			return error(_("%s: bad revision"), name);
 	}
