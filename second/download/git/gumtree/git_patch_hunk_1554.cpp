 }
 
 static int add_info_ref(const char *path, const struct object_id *oid,
 			int flag, void *cb_data)
 {
 	FILE *fp = cb_data;
-	struct object *o = parse_object(oid->hash);
+	struct object *o = parse_object(oid);
 	if (!o)
 		return -1;
 
 	if (fprintf(fp, "%s	%s\n", oid_to_hex(oid), path) < 0)
 		return -1;
 
