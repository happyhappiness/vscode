 
 static void batch_object_write(const char *obj_name, struct batch_options *opt,
 			       struct expand_data *data)
 {
 	struct strbuf buf = STRBUF_INIT;
 
-	if (sha1_object_info_extended(data->sha1, &data->info, LOOKUP_REPLACE_OBJECT) < 0) {
+	if (!data->skip_object_info &&
+	    sha1_object_info_extended(data->sha1, &data->info, LOOKUP_REPLACE_OBJECT) < 0) {
 		printf("%s missing\n", obj_name ? obj_name : sha1_to_hex(data->sha1));
 		fflush(stdout);
 		return;
 	}
 
 	strbuf_expand(&buf, opt->format, expand_format, data);
