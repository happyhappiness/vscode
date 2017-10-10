 	objects = rev.pending.objects;
 	for (i = 0; i < count && !ret; i++) {
 		struct object *o = objects[i].item;
 		const char *name = objects[i].name;
 		switch (o->type) {
 		case OBJ_BLOB:
-			ret = show_blob_object(o->sha1, &rev, name);
+			ret = show_blob_object(o->oid.hash, &rev, name);
 			break;
 		case OBJ_TAG: {
 			struct tag *t = (struct tag *)o;
 
 			if (rev.shown_one)
 				putchar('\n');
 			printf("%stag %s%s\n",
 					diff_get_color_opt(&rev.diffopt, DIFF_COMMIT),
 					t->tag,
 					diff_get_color_opt(&rev.diffopt, DIFF_RESET));
-			ret = show_tag_object(o->sha1, &rev);
+			ret = show_tag_object(o->oid.hash, &rev);
 			rev.shown_one = 1;
 			if (ret)
 				break;
-			o = parse_object(t->tagged->sha1);
+			o = parse_object(t->tagged->oid.hash);
 			if (!o)
 				ret = error(_("Could not read object %s"),
-					    sha1_to_hex(t->tagged->sha1));
+					    oid_to_hex(&t->tagged->oid));
 			objects[i].item = o;
 			i--;
 			break;
 		}
 		case OBJ_TREE:
 			if (rev.shown_one)
