 	item->buffer = buffer;
 	item->size = size;
 
 	return 0;
 }
 
-int parse_tree(struct tree *item)
+int parse_tree_gently(struct tree *item, int quiet_on_missing)
 {
 	 enum object_type type;
 	 void *buffer;
 	 unsigned long size;
 
 	if (item->object.parsed)
 		return 0;
 	buffer = read_sha1_file(item->object.sha1, &type, &size);
 	if (!buffer)
-		return error("Could not read %s",
+		return quiet_on_missing ? -1 :
+			error("Could not read %s",
 			     sha1_to_hex(item->object.sha1));
 	if (type != OBJ_TREE) {
 		free(buffer);
 		return error("Object %s not a tree",
 			     sha1_to_hex(item->object.sha1));
 	}
