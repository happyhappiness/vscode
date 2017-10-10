 	for (i = 0; i < rev.pending.nr; i++) {
 		struct object_array_entry *entry = &rev.pending.objects[i];
 		struct object *obj = entry->item;
 		const char *name = entry->name;
 		int flags = (obj->flags & UNINTERESTING);
 		if (!obj->parsed)
-			obj = parse_object(obj->sha1);
+			obj = parse_object(obj->oid.hash);
 		obj = deref_tag(obj, NULL, 0);
 		if (!obj)
 			die(_("invalid object '%s' given."), name);
 		if (obj->type == OBJ_COMMIT)
 			obj = &((struct commit *)obj)->tree->object;
 
 		if (obj->type == OBJ_TREE) {
 			obj->flags |= flags;
 			add_object_array(obj, name, &ent);
 		} else if (obj->type == OBJ_BLOB) {
 			if (2 <= blobs)
 				die(_("more than two blobs given: '%s'"), name);
-			hashcpy(blob[blobs].sha1, obj->sha1);
+			hashcpy(blob[blobs].sha1, obj->oid.hash);
 			blob[blobs].name = name;
 			blob[blobs].mode = entry->mode;
 			blobs++;
 
 		} else {
 			die(_("unhandled object '%s' given."), name);
