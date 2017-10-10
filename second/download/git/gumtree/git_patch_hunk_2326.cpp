 		unlink(tmp);
 	}
 	free(tmp);
 	return ret;
 }
 
-static int add_info_ref(const char *path, const unsigned char *sha1, int flag, void *cb_data)
+static int add_info_ref(const char *path, const struct object_id *oid,
+			int flag, void *cb_data)
 {
 	FILE *fp = cb_data;
-	struct object *o = parse_object(sha1);
+	struct object *o = parse_object(oid->hash);
 	if (!o)
 		return -1;
 
-	if (fprintf(fp, "%s	%s\n", sha1_to_hex(sha1), path) < 0)
+	if (fprintf(fp, "%s	%s\n", oid_to_hex(oid), path) < 0)
 		return -1;
 
 	if (o->type == OBJ_TAG) {
 		o = deref_tag(o, path, 0);
 		if (o)
 			if (fprintf(fp, "%s	%s^{}\n",
