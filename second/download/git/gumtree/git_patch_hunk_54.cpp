 }
 
 struct tree *lookup_tree(const unsigned char *sha1)
 {
 	struct object *obj = lookup_object(sha1);
 	if (!obj)
-		return create_object(sha1, OBJ_TREE, alloc_tree_node());
-	if (!obj->type)
-		obj->type = OBJ_TREE;
-	if (obj->type != OBJ_TREE) {
-		error("Object %s is a %s, not a tree",
-		      sha1_to_hex(sha1), typename(obj->type));
-		return NULL;
-	}
-	return (struct tree *) obj;
+		return create_object(sha1, alloc_tree_node());
+	return object_as_type(obj, OBJ_TREE, 0);
 }
 
 int parse_tree_buffer(struct tree *item, void *buffer, unsigned long size)
 {
 	if (item->object.parsed)
 		return 0;
