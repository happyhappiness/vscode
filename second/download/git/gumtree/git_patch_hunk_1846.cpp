 		show_commit(commit, data);
 	}
 	for (i = 0; i < revs->pending.nr; i++) {
 		struct object_array_entry *pending = revs->pending.objects + i;
 		struct object *obj = pending->item;
 		const char *name = pending->name;
+		const char *path = pending->path;
 		if (obj->flags & (UNINTERESTING | SEEN))
 			continue;
 		if (obj->type == OBJ_TAG) {
 			obj->flags |= SEEN;
 			show_object(obj, NULL, name, data);
 			continue;
 		}
+		if (!path)
+			path = "";
 		if (obj->type == OBJ_TREE) {
 			process_tree(revs, (struct tree *)obj, show_object,
-				     NULL, &base, name, data);
+				     NULL, &base, path, data);
 			continue;
 		}
 		if (obj->type == OBJ_BLOB) {
 			process_blob(revs, (struct blob *)obj, show_object,
-				     NULL, name, data);
+				     NULL, path, data);
 			continue;
 		}
 		die("unknown pending object %s (%s)",
 		    sha1_to_hex(obj->sha1), name);
 	}
-	if (revs->pending.nr) {
-		free(revs->pending.objects);
-		revs->pending.nr = 0;
-		revs->pending.alloc = 0;
-		revs->pending.objects = NULL;
-	}
+	object_array_clear(&revs->pending);
 	strbuf_release(&base);
 }
