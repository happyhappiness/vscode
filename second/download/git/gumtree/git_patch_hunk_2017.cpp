 			    final_commit_name);
 		sb->final = (struct commit *) obj;
 		final_commit_name = revs->pending.objects[i].name;
 	}
 	if (!final_commit_name)
 		die("No commit to dig down to?");
-	return final_commit_name;
+	return xstrdup(final_commit_name);
 }
 
 static int blame_copy_callback(const struct option *option, const char *arg, int unset)
 {
 	int *opt = option->value;
 
