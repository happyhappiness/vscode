 	 */
 	cache_tree_invalidate_path(&the_index, path);
 
 	return commit;
 }
 
-static char *prepare_final(struct scoreboard *sb)
+static struct commit *find_single_final(struct rev_info *revs,
+					const char **name_p)
 {
 	int i;
-	const char *final_commit_name = NULL;
-	struct rev_info *revs = sb->revs;
+	struct commit *found = NULL;
+	const char *name = NULL;
 
-	/*
-	 * There must be one and only one positive commit in the
-	 * revs->pending array.
-	 */
 	for (i = 0; i < revs->pending.nr; i++) {
 		struct object *obj = revs->pending.objects[i].item;
 		if (obj->flags & UNINTERESTING)
 			continue;
 		while (obj->type == OBJ_TAG)
 			obj = deref_tag(obj, NULL, 0);
 		if (obj->type != OBJ_COMMIT)
 			die("Non commit %s?", revs->pending.objects[i].name);
-		if (sb->final)
+		if (found)
 			die("More than one commit to dig from %s and %s?",
-			    revs->pending.objects[i].name,
-			    final_commit_name);
-		sb->final = (struct commit *) obj;
-		final_commit_name = revs->pending.objects[i].name;
-	}
-	return xstrdup_or_null(final_commit_name);
+			    revs->pending.objects[i].name, name);
+		found = (struct commit *)obj;
+		name = revs->pending.objects[i].name;
+	}
+	if (name_p)
+		*name_p = name;
+	return found;
+}
+
+static char *prepare_final(struct scoreboard *sb)
+{
+	const char *name;
+	sb->final = find_single_final(sb->revs, &name);
+	return xstrdup_or_null(name);
 }
 
 static char *prepare_initial(struct scoreboard *sb)
 {
 	int i;
 	const char *final_commit_name = NULL;
