 	objects = rev.pending.objects;
 	for (i = 0; i < count && !ret; i++) {
 		struct object *o = objects[i].item;
 		const char *name = objects[i].name;
 		switch (o->type) {
 		case OBJ_BLOB:
-			ret = show_blob_object(o->oid.hash, &rev, name);
+			ret = show_blob_object(&o->oid, &rev, name);
 			break;
 		case OBJ_TAG: {
 			struct tag *t = (struct tag *)o;
 
 			if (rev.shown_one)
 				putchar('\n');
 			fprintf(rev.diffopt.file, "%stag %s%s\n",
 					diff_get_color_opt(&rev.diffopt, DIFF_COMMIT),
 					t->tag,
 					diff_get_color_opt(&rev.diffopt, DIFF_RESET));
-			ret = show_tag_object(o->oid.hash, &rev);
+			ret = show_tag_object(&o->oid, &rev);
 			rev.shown_one = 1;
 			if (ret)
 				break;
 			o = parse_object(t->tagged->oid.hash);
 			if (!o)
 				ret = error(_("Could not read object %s"),
