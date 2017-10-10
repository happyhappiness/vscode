 	for (i = 0; i < rev.pending.nr; i++) {
 		struct object_array_entry *entry = &rev.pending.objects[i];
 		struct object *obj = entry->item;
 		const char *name = entry->name;
 		int flags = (obj->flags & UNINTERESTING);
 		if (!obj->parsed)
-			obj = parse_object(obj->oid.hash);
+			obj = parse_object(&obj->oid);
 		obj = deref_tag(obj, NULL, 0);
 		if (!obj)
 			die(_("invalid object '%s' given."), name);
 		if (obj->type == OBJ_COMMIT)
 			obj = &((struct commit *)obj)->tree->object;
 
