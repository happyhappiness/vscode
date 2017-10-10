 	while (tree_entry(&desc, &entry)) {
 		int result;
 
 		if (S_ISGITLINK(entry.mode))
 			continue;
 		if (S_ISDIR(entry.mode))
-			result = walk(&lookup_tree(entry.sha1)->object, OBJ_TREE, data);
+			result = options->walk(&lookup_tree(entry.sha1)->object, OBJ_TREE, data, options);
 		else if (S_ISREG(entry.mode) || S_ISLNK(entry.mode))
-			result = walk(&lookup_blob(entry.sha1)->object, OBJ_BLOB, data);
+			result = options->walk(&lookup_blob(entry.sha1)->object, OBJ_BLOB, data, options);
 		else {
 			result = error("in tree %s: entry %s has bad mode %.6o",
 					sha1_to_hex(tree->object.sha1), entry.path, entry.mode);
 		}
 		if (result < 0)
 			return result;
 		if (!res)
 			res = result;
 	}
 	return res;
 }
 
-static int fsck_walk_commit(struct commit *commit, fsck_walk_func walk, void *data)
+static int fsck_walk_commit(struct commit *commit, void *data, struct fsck_options *options)
 {
 	struct commit_list *parents;
 	int res;
 	int result;
 
 	if (parse_commit(commit))
 		return -1;
 
-	result = walk((struct object *)commit->tree, OBJ_TREE, data);
+	result = options->walk((struct object *)commit->tree, OBJ_TREE, data, options);
 	if (result < 0)
 		return result;
 	res = result;
 
 	parents = commit->parents;
 	while (parents) {
-		result = walk((struct object *)parents->item, OBJ_COMMIT, data);
+		result = options->walk((struct object *)parents->item, OBJ_COMMIT, data, options);
 		if (result < 0)
 			return result;
 		if (!res)
 			res = result;
 		parents = parents->next;
 	}
 	return res;
 }
 
-static int fsck_walk_tag(struct tag *tag, fsck_walk_func walk, void *data)
+static int fsck_walk_tag(struct tag *tag, void *data, struct fsck_options *options)
 {
 	if (parse_tag(tag))
 		return -1;
-	return walk(tag->tagged, OBJ_ANY, data);
+	return options->walk(tag->tagged, OBJ_ANY, data, options);
 }
 
-int fsck_walk(struct object *obj, fsck_walk_func walk, void *data)
+int fsck_walk(struct object *obj, void *data, struct fsck_options *options)
 {
 	if (!obj)
 		return -1;
 	switch (obj->type) {
 	case OBJ_BLOB:
 		return 0;
 	case OBJ_TREE:
-		return fsck_walk_tree((struct tree *)obj, walk, data);
+		return fsck_walk_tree((struct tree *)obj, data, options);
 	case OBJ_COMMIT:
-		return fsck_walk_commit((struct commit *)obj, walk, data);
+		return fsck_walk_commit((struct commit *)obj, data, options);
 	case OBJ_TAG:
-		return fsck_walk_tag((struct tag *)obj, walk, data);
+		return fsck_walk_tag((struct tag *)obj, data, options);
 	default:
 		error("Unknown object type for %s", sha1_to_hex(obj->sha1));
 		return -1;
 	}
 }
 
