 			break;
 		case OBJ_TAG: {
 			struct tag *t = (struct tag *)o;
 
 			if (rev.shown_one)
 				putchar('\n');
-			printf("%stag %s%s\n",
+			fprintf(rev.diffopt.file, "%stag %s%s\n",
 					diff_get_color_opt(&rev.diffopt, DIFF_COMMIT),
 					t->tag,
 					diff_get_color_opt(&rev.diffopt, DIFF_RESET));
 			ret = show_tag_object(o->oid.hash, &rev);
 			rev.shown_one = 1;
 			if (ret)
