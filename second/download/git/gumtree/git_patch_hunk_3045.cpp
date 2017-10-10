 		if (process_tag(walker, (struct tag *)obj))
 			return -1;
 		return 0;
 	}
 	return error("Unable to determine requirements "
 		     "of type %s for %s",
-		     typename(obj->type), sha1_to_hex(obj->sha1));
+		     typename(obj->type), oid_to_hex(&obj->oid));
 }
 
 static int process(struct walker *walker, struct object *obj)
 {
 	if (obj->flags & SEEN)
 		return 0;
 	obj->flags |= SEEN;
 
-	if (has_sha1_file(obj->sha1)) {
+	if (has_object_file(&obj->oid)) {
 		/* We already have it, so we should scan it now. */
 		obj->flags |= TO_SCAN;
 	}
 	else {
 		if (obj->flags & COMPLETE)
 			return 0;
-		walker->prefetch(walker, obj->sha1);
+		walker->prefetch(walker, obj->oid.hash);
 	}
 
 	object_list_insert(obj, process_queue_end);
 	process_queue_end = &(*process_queue_end)->next;
 	return 0;
 }
