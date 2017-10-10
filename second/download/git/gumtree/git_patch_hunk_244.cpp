 
 	/* get all revisions that merge commit a */
 	snprintf(merged_revision, sizeof(merged_revision), "^%s",
 			sha1_to_hex(a->object.sha1));
 	init_revisions(&revs, NULL);
 	rev_opts.submodule = path;
-	setup_revisions(sizeof(rev_args)/sizeof(char *)-1, rev_args, &revs, &rev_opts);
+	setup_revisions(ARRAY_SIZE(rev_args)-1, rev_args, &revs, &rev_opts);
 
 	/* save all revisions from the above list that contain b */
 	if (prepare_revision_walk(&revs))
 		die("revision walk setup failed");
 	while ((commit = get_revision(&revs)) != NULL) {
 		struct object *o = &(commit->object);
