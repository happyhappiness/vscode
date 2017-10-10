 	while (object->type == OBJ_TAG) {
 		struct tag *tag = (struct tag *) object;
 		if (revs->tag_objects && !(flags & UNINTERESTING))
 			add_pending_object(revs, object, tag->tag);
 		if (!tag->tagged)
 			die("bad tag");
-		object = parse_object(tag->tagged->oid.hash);
+		object = parse_object(&tag->tagged->oid);
 		if (!object) {
 			if (revs->ignore_missing_links || (flags & UNINTERESTING))
 				return NULL;
 			die("bad object %s", oid_to_hex(&tag->tagged->oid));
 		}
 		object->flags |= flags;
