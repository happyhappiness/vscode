 
 	if (0 <= it->entry_count) {
 		struct object *obj = parse_object(it->sha1);
 		if (!obj) {
 			error("%s: invalid sha1 pointer in cache-tree",
 			      sha1_to_hex(it->sha1));
+			errors_found |= ERROR_REFS;
 			return 1;
 		}
 		obj->used = 1;
 		mark_object_reachable(obj);
 		if (obj->type != OBJ_TREE)
 			err |= objerror(obj, "non-tree in cache-tree");
