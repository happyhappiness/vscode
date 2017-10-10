  * to be checked at the end.
  */
 static void write_object(unsigned nr, enum object_type type,
 			 void *buf, unsigned long size)
 {
 	if (!strict) {
-		if (write_sha1_file(buf, size, typename(type), obj_list[nr].sha1) < 0)
+		if (write_sha1_file(buf, size, typename(type), obj_list[nr].oid.hash) < 0)
 			die("failed to write object");
 		added_object(nr, type, buf, size);
 		free(buf);
 		obj_list[nr].obj = NULL;
 	} else if (type == OBJ_BLOB) {
 		struct blob *blob;
-		if (write_sha1_file(buf, size, typename(type), obj_list[nr].sha1) < 0)
+		if (write_sha1_file(buf, size, typename(type), obj_list[nr].oid.hash) < 0)
 			die("failed to write object");
 		added_object(nr, type, buf, size);
 		free(buf);
 
-		blob = lookup_blob(obj_list[nr].sha1);
+		blob = lookup_blob(&obj_list[nr].oid);
 		if (blob)
 			blob->object.flags |= FLAG_WRITTEN;
 		else
 			die("invalid blob object");
 		obj_list[nr].obj = NULL;
 	} else {
 		struct object *obj;
 		int eaten;
-		hash_sha1_file(buf, size, typename(type), obj_list[nr].sha1);
+		hash_sha1_file(buf, size, typename(type), obj_list[nr].oid.hash);
 		added_object(nr, type, buf, size);
-		obj = parse_object_buffer(obj_list[nr].sha1, type, size, buf, &eaten);
+		obj = parse_object_buffer(&obj_list[nr].oid, type, size, buf,
+					  &eaten);
 		if (!obj)
 			die("invalid %s", typename(type));
 		add_object_buffer(obj, buf, size);
 		obj->flags |= FLAG_OPEN;
 		obj_list[nr].obj = obj;
 	}
