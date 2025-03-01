 		if (!(obj->flags & UNINTERESTING))
 			continue;
 		obj = deref_tag(obj, NULL, 0);
 		if (obj->type != OBJ_COMMIT)
 			die("Non commit %s?", revs->pending.objects[i].name);
 		if (sb->final)
-			die("More than one commit to dig down to %s and %s?",
+			die("More than one commit to dig up from, %s and %s?",
 			    revs->pending.objects[i].name,
 			    final_commit_name);
 		sb->final = (struct commit *) obj;
 		final_commit_name = revs->pending.objects[i].name;
 	}
+
+	if (!final_commit_name)
+		final_commit_name = dwim_reverse_initial(sb);
 	if (!final_commit_name)
-		die("No commit to dig down to?");
+		die("No commit to dig up from?");
 	return xstrdup(final_commit_name);
 }
 
 static int blame_copy_callback(const struct option *option, const char *arg, int unset)
 {
 	int *opt = option->value;
