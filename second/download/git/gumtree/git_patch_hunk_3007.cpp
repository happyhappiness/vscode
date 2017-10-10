 	while (object->type == OBJ_TAG) {
 		struct tag *tag = (struct tag *) object;
 		if (revs->tag_objects && !(flags & UNINTERESTING))
 			add_pending_object(revs, object, tag->tag);
 		if (!tag->tagged)
 			die("bad tag");
-		object = parse_object(tag->tagged->sha1);
+		object = parse_object(tag->tagged->oid.hash);
 		if (!object) {
 			if (flags & UNINTERESTING)
 				return NULL;
-			die("bad object %s", sha1_to_hex(tag->tagged->sha1));
+			die("bad object %s", oid_to_hex(&tag->tagged->oid));
 		}
 		object->flags |= flags;
 		/*
 		 * We'll handle the tagged object by looping or dropping
 		 * through to the non-tag handlers below. Do not
 		 * propagate path data from the tag's pending entry.
