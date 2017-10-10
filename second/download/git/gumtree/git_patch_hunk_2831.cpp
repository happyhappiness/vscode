 static int mark_link(struct object *obj, int type, void *data, struct fsck_options *options)
 {
 	if (!obj)
 		return -1;
 
 	if (type != OBJ_ANY && obj->type != type)
-		die(_("object type mismatch at %s"), sha1_to_hex(obj->sha1));
+		die(_("object type mismatch at %s"), oid_to_hex(&obj->oid));
 
 	obj->flags |= FLAG_LINK;
 	return 0;
 }
 
 /* The content of each linked object must have been checked
