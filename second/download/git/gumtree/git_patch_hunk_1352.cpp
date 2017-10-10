 
 static int show_reference(const char *refname, const struct object_id *oid,
 			  int flag, void *cb_data)
 {
 	struct show_data *data = cb_data;
 
-	if (!wildmatch(data->pattern, refname, 0, NULL)) {
+	if (!wildmatch(data->pattern, refname, 0)) {
 		if (data->format == REPLACE_FORMAT_SHORT)
 			printf("%s\n", refname);
 		else if (data->format == REPLACE_FORMAT_MEDIUM)
 			printf("%s -> %s\n", refname, oid_to_hex(oid));
 		else { /* data->format == REPLACE_FORMAT_LONG */
 			struct object_id object;
