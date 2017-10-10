 		return -1;
 
 	if (o->type == OBJ_TAG) {
 		o = deref_tag(o, path, 0);
 		if (o)
 			if (fprintf(fp, "%s	%s^{}\n",
-				sha1_to_hex(o->sha1), path) < 0)
+				oid_to_hex(&o->oid), path) < 0)
 				return -1;
 	}
 	return 0;
 }
 
 static int generate_info_refs(FILE *fp)
