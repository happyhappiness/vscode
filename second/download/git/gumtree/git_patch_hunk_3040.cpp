 	 enum object_type type;
 	 void *buffer;
 	 unsigned long size;
 
 	if (item->object.parsed)
 		return 0;
-	buffer = read_sha1_file(item->object.sha1, &type, &size);
+	buffer = read_sha1_file(item->object.oid.hash, &type, &size);
 	if (!buffer)
 		return quiet_on_missing ? -1 :
 			error("Could not read %s",
-			     sha1_to_hex(item->object.sha1));
+			     oid_to_hex(&item->object.oid));
 	if (type != OBJ_TREE) {
 		free(buffer);
 		return error("Object %s not a tree",
-			     sha1_to_hex(item->object.sha1));
+			     oid_to_hex(&item->object.oid));
 	}
 	return parse_tree_buffer(item, buffer, size);
 }
 
 void free_tree_buffer(struct tree *tree)
 {
