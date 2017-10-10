 	int ret;
 
 	if (!item)
 		return -1;
 	if (item->object.parsed)
 		return 0;
-	buffer = read_sha1_file(item->object.sha1, &type, &size);
+	buffer = read_sha1_file(item->object.oid.hash, &type, &size);
 	if (!buffer)
 		return quiet_on_missing ? -1 :
 			error("Could not read %s",
-			     sha1_to_hex(item->object.sha1));
+			     oid_to_hex(&item->object.oid));
 	if (type != OBJ_COMMIT) {
 		free(buffer);
 		return error("Object %s not a commit",
-			     sha1_to_hex(item->object.sha1));
+			     oid_to_hex(&item->object.oid));
 	}
 	ret = parse_commit_buffer(item, buffer, size);
 	if (save_commit_buffer && !ret) {
 		set_commit_buffer(item, buffer, size);
 		return 0;
 	}
