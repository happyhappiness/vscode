 	if (commit_lock_file(lock))
 		die("could not close alternates file");
 	if (alt_odb_tail)
 		link_alt_odb_entries(alt, strlen(alt), '\n', NULL, 0);
 }
 
-void foreach_alt_odb(alt_odb_fn fn, void *cb)
+int foreach_alt_odb(alt_odb_fn fn, void *cb)
 {
 	struct alternate_object_database *ent;
+	int r = 0;
 
 	prepare_alt_odb();
-	for (ent = alt_odb_list; ent; ent = ent->next)
-		if (fn(ent, cb))
-			return;
+	for (ent = alt_odb_list; ent; ent = ent->next) {
+		r = fn(ent, cb);
+		if (r)
+			break;
+	}
+	return r;
 }
 
 void prepare_alt_odb(void)
 {
 	const char *alt;
 
