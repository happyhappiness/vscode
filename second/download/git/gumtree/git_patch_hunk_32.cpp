 		free(buffer);
 		return error("Object %s not a commit",
 			     sha1_to_hex(item->object.sha1));
 	}
 	ret = parse_commit_buffer(item, buffer, size);
 	if (save_commit_buffer && !ret) {
-		item->buffer = buffer;
+		set_commit_buffer(item, buffer, size);
 		return 0;
 	}
 	free(buffer);
 	return ret;
 }
 
