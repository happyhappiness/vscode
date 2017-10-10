 	memset(&old, 0, sizeof(old));
 	old.path = path_to_free = resolve_refdup("HEAD", rev, 0, &flag);
 	old.commit = lookup_commit_reference_gently(rev, 1);
 	if (!(flag & REF_ISSYMREF))
 		old.path = NULL;
 
-	if (old.path && starts_with(old.path, "refs/heads/"))
-		old.name = old.path + strlen("refs/heads/");
+	if (old.path)
+		skip_prefix(old.path, "refs/heads/", &old.name);
 
 	if (!new->name) {
 		new->name = "HEAD";
 		new->commit = old.commit;
 		if (!new->commit)
 			die(_("You are on a branch yet to be born"));
