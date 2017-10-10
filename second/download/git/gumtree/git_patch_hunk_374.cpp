 	} else if ((base_commit && !strcmp(base_commit, "auto")) || base_auto) {
 		struct branch *curr_branch = branch_get(NULL);
 		const char *upstream = branch_get_upstream(curr_branch, NULL);
 		if (upstream) {
 			struct commit_list *base_list;
 			struct commit *commit;
-			unsigned char sha1[20];
+			struct object_id oid;
 
-			if (get_sha1(upstream, sha1))
+			if (get_oid(upstream, &oid))
 				die(_("Failed to resolve '%s' as a valid ref."), upstream);
-			commit = lookup_commit_or_die(sha1, "upstream base");
+			commit = lookup_commit_or_die(oid.hash, "upstream base");
 			base_list = get_merge_bases_many(commit, total, list);
 			/* There should be one and only one merge base. */
 			if (!base_list || base_list->next)
 				die(_("Could not find exact merge base."));
 			base = base_list->item;
 			free_commit_list(base_list);
