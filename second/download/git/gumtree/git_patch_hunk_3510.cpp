 	return git_default_config(var, value, cb);
 }
 
 static void verify_working_tree_path(struct commit *work_tree, const char *path)
 {
 	struct commit_list *parents;
+	int pos;
 
 	for (parents = work_tree->parents; parents; parents = parents->next) {
 		const unsigned char *commit_sha1 = parents->item->object.oid.hash;
 		unsigned char blob_sha1[20];
 		unsigned mode;
 
 		if (!get_tree_entry(commit_sha1, path, blob_sha1, &mode) &&
 		    sha1_object_info(blob_sha1, NULL) == OBJ_BLOB)
 			return;
 	}
-	die("no such path '%s' in HEAD", path);
+
+	pos = cache_name_pos(path, strlen(path));
+	if (pos >= 0)
+		; /* path is in the index */
+	else if (!strcmp(active_cache[-1 - pos]->name, path))
+		; /* path is in the index, unmerged */
+	else
+		die("no such path '%s' in HEAD", path);
 }
 
 static struct commit_list **append_parent(struct commit_list **tail, const unsigned char *sha1)
 {
 	struct commit *parent;
 
