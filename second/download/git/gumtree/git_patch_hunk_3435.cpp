 	git_config(git_default_config, NULL);
 	dir = opendir(git_path("rr-cache"));
 	if (!dir)
 		die_errno("unable to open rr-cache directory");
 	/* Collect stale conflict IDs ... */
 	while ((e = readdir(dir))) {
+		struct rerere_dir *rr_dir;
+		struct rerere_id id;
+		int now_empty;
+
 		if (is_dot_or_dotdot(e->d_name))
 			continue;
-
-		then = rerere_last_used_at(e->d_name);
-		if (then) {
-			cutoff = cutoff_resolve;
-		} else {
-			then = rerere_created_at(e->d_name);
-			if (!then)
-				continue;
-			cutoff = cutoff_noresolve;
+		rr_dir = find_rerere_dir(e->d_name);
+		if (!rr_dir)
+			continue; /* or should we remove e->d_name? */
+
+		now_empty = 1;
+		for (id.variant = 0, id.collection = rr_dir;
+		     id.variant < id.collection->status_nr;
+		     id.variant++) {
+			prune_one(&id, now, cutoff_resolve, cutoff_noresolve);
+			if (id.collection->status[id.variant])
+				now_empty = 0;
 		}
-		if (then < now - cutoff * 86400)
+		if (now_empty)
 			string_list_append(&to_remove, e->d_name);
 	}
 	closedir(dir);
-	/* ... and then remove them one-by-one */
+
+	/* ... and then remove the empty directories */
 	for (i = 0; i < to_remove.nr; i++)
-		unlink_rr_item(dirname_to_id(to_remove.items[i].string));
+		rmdir(git_path("rr-cache/%s", to_remove.items[i].string));
 	string_list_clear(&to_remove, 0);
 	rollback_lock_file(&write_lock);
 }
 
 /*
  * During a conflict resolution, after "rerere" recorded the
