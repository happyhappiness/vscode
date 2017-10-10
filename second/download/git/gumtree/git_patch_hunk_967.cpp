 	mergetag_data.argv = argv;
 	for_each_mergetag(check_one_mergetag, commit, &mergetag_data);
 }
 
 static int create_graft(int argc, const char **argv, int force)
 {
-	unsigned char old[20], new[20];
+	struct object_id old, new;
 	const char *old_ref = argv[0];
 	struct commit *commit;
 	struct strbuf buf = STRBUF_INIT;
 	const char *buffer;
 	unsigned long size;
 
-	if (get_sha1(old_ref, old) < 0)
+	if (get_oid(old_ref, &old) < 0)
 		die(_("Not a valid object name: '%s'"), old_ref);
-	commit = lookup_commit_or_die(old, old_ref);
+	commit = lookup_commit_or_die(old.hash, old_ref);
 
 	buffer = get_commit_buffer(commit, &size);
 	strbuf_add(&buf, buffer, size);
 	unuse_commit_buffer(commit, buffer);
 
 	replace_parents(&buf, argc - 1, &argv[1]);
