 		return (struct commit *)e->item;
 	case OBJ_TAG: {
 		struct tag *tag = (struct tag *)e->item;
 
 		/* handle nested tags */
 		while (tag && tag->object.type == OBJ_TAG) {
-			parse_object(tag->object.oid.hash);
+			parse_object(&tag->object.oid);
 			string_list_append(&extra_refs, full_name)->util = tag;
 			tag = (struct tag *)tag->tagged;
 		}
 		if (!tag)
 			die("Tag %s points nowhere?", e->name);
 		return (struct commit *)tag;
