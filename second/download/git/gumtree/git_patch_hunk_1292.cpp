 					t->tag,
 					diff_get_color_opt(&rev.diffopt, DIFF_RESET));
 			ret = show_tag_object(&o->oid, &rev);
 			rev.shown_one = 1;
 			if (ret)
 				break;
-			o = parse_object(t->tagged->oid.hash);
+			o = parse_object(&t->tagged->oid);
 			if (!o)
 				ret = error(_("Could not read object %s"),
 					    oid_to_hex(&t->tagged->oid));
 			objects[i].item = o;
 			i--;
 			break;
