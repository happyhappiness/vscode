 		if (!obj) {
 			error("%s: invalid sha1 pointer in cache-tree",
 			      oid_to_hex(&it->oid));
 			errors_found |= ERROR_REFS;
 			return 1;
 		}
-		obj->used = 1;
+		obj->flags |= USED;
 		if (name_objects)
 			add_decoration(fsck_walk_options.object_names,
 				obj, xstrdup(":"));
 		mark_object_reachable(obj);
 		if (obj->type != OBJ_TREE)
 			err |= objerror(obj, "non-tree in cache-tree");
