 	struct object *obj = lookup_object(sha1);
 	if (!obj)
 		obj = create_object(sha1, alloc_object_node());
 	return obj;
 }
 
-struct object *parse_object_buffer(const unsigned char *sha1, enum object_type type, unsigned long size, void *buffer, int *eaten_p)
+struct object *parse_object_buffer(const struct object_id *oid, enum object_type type, unsigned long size, void *buffer, int *eaten_p)
 {
 	struct object *obj;
 	*eaten_p = 0;
 
 	obj = NULL;
 	if (type == OBJ_BLOB) {
-		struct blob *blob = lookup_blob(sha1);
+		struct blob *blob = lookup_blob(oid);
 		if (blob) {
 			if (parse_blob_buffer(blob, buffer, size))
 				return NULL;
 			obj = &blob->object;
 		}
 	} else if (type == OBJ_TREE) {
-		struct tree *tree = lookup_tree(sha1);
+		struct tree *tree = lookup_tree(oid);
 		if (tree) {
 			obj = &tree->object;
 			if (!tree->buffer)
 				tree->object.parsed = 0;
 			if (!tree->object.parsed) {
 				if (parse_tree_buffer(tree, buffer, size))
 					return NULL;
 				*eaten_p = 1;
 			}
 		}
 	} else if (type == OBJ_COMMIT) {
-		struct commit *commit = lookup_commit(sha1);
+		struct commit *commit = lookup_commit(oid);
 		if (commit) {
 			if (parse_commit_buffer(commit, buffer, size))
 				return NULL;
 			if (!get_cached_commit_buffer(commit, NULL)) {
 				set_commit_buffer(commit, buffer, size);
 				*eaten_p = 1;
 			}
 			obj = &commit->object;
 		}
 	} else if (type == OBJ_TAG) {
-		struct tag *tag = lookup_tag(sha1);
+		struct tag *tag = lookup_tag(oid);
 		if (tag) {
 			if (parse_tag_buffer(tag, buffer, size))
 			       return NULL;
 			obj = &tag->object;
 		}
 	} else {
-		warning("object %s has unknown type id %d", sha1_to_hex(sha1), type);
+		warning("object %s has unknown type id %d", oid_to_hex(oid), type);
 		obj = NULL;
 	}
 	return obj;
 }
 
-struct object *parse_object_or_die(const unsigned char *sha1,
+struct object *parse_object_or_die(const struct object_id *oid,
 				   const char *name)
 {
-	struct object *o = parse_object(sha1);
+	struct object *o = parse_object(oid);
 	if (o)
 		return o;
 
-	die(_("unable to parse object: %s"), name ? name : sha1_to_hex(sha1));
+	die(_("unable to parse object: %s"), name ? name : oid_to_hex(oid));
 }
 
-struct object *parse_object(const unsigned char *sha1)
+struct object *parse_object(const struct object_id *oid)
 {
 	unsigned long size;
 	enum object_type type;
 	int eaten;
-	const unsigned char *repl = lookup_replace_object(sha1);
+	const unsigned char *repl = lookup_replace_object(oid->hash);
 	void *buffer;
 	struct object *obj;
 
-	obj = lookup_object(sha1);
+	obj = lookup_object(oid->hash);
 	if (obj && obj->parsed)
 		return obj;
 
 	if ((obj && obj->type == OBJ_BLOB) ||
-	    (!obj && has_sha1_file(sha1) &&
-	     sha1_object_info(sha1, NULL) == OBJ_BLOB)) {
+	    (!obj && has_object_file(oid) &&
+	     sha1_object_info(oid->hash, NULL) == OBJ_BLOB)) {
 		if (check_sha1_signature(repl, NULL, 0, NULL) < 0) {
-			error("sha1 mismatch %s", sha1_to_hex(repl));
+			error("sha1 mismatch %s", oid_to_hex(oid));
 			return NULL;
 		}
-		parse_blob_buffer(lookup_blob(sha1), NULL, 0);
-		return lookup_object(sha1);
+		parse_blob_buffer(lookup_blob(oid), NULL, 0);
+		return lookup_object(oid->hash);
 	}
 
-	buffer = read_sha1_file(sha1, &type, &size);
+	buffer = read_sha1_file(oid->hash, &type, &size);
 	if (buffer) {
 		if (check_sha1_signature(repl, buffer, size, typename(type)) < 0) {
 			free(buffer);
 			error("sha1 mismatch %s", sha1_to_hex(repl));
 			return NULL;
 		}
 
-		obj = parse_object_buffer(sha1, type, size, buffer, &eaten);
+		obj = parse_object_buffer(oid, type, size, buffer, &eaten);
 		if (!eaten)
 			free(buffer);
 		return obj;
 	}
 	return NULL;
 }
