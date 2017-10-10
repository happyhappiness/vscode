 			die("object %s disappeared", sha1_to_hex(sha1));
 		if (type != data->type)
 			die("object %s changed type!?", sha1_to_hex(sha1));
 		if (data->info.sizep && size != data->size)
 			die("object %s changed size!?", sha1_to_hex(sha1));
 
-		write_or_die(fd, contents, size);
+		batch_write(opt, contents, size);
 		free(contents);
 	}
 }
 
-struct batch_options {
-	int enabled;
-	int follow_symlinks;
-	int print_contents;
-	const char *format;
-};
-
-static int batch_one_object(const char *obj_name, struct batch_options *opt,
-			    struct expand_data *data)
+static void batch_object_write(const char *obj_name, struct batch_options *opt,
+			       struct expand_data *data)
 {
 	struct strbuf buf = STRBUF_INIT;
+
+	if (sha1_object_info_extended(data->sha1, &data->info, LOOKUP_REPLACE_OBJECT) < 0) {
+		printf("%s missing\n", obj_name ? obj_name : sha1_to_hex(data->sha1));
+		fflush(stdout);
+		return;
+	}
+
+	strbuf_expand(&buf, opt->format, expand_format, data);
+	strbuf_addch(&buf, '\n');
+	batch_write(opt, buf.buf, buf.len);
+	strbuf_release(&buf);
+
+	if (opt->print_contents) {
+		print_object_or_die(opt, data);
+		batch_write(opt, "\n", 1);
+	}
+}
+
+static void batch_one_object(const char *obj_name, struct batch_options *opt,
+			     struct expand_data *data)
+{
 	struct object_context ctx;
 	int flags = opt->follow_symlinks ? GET_SHA1_FOLLOW_SYMLINKS : 0;
 	enum follow_symlinks_result result;
 
-	if (!obj_name)
-	   return 1;
-
 	result = get_sha1_with_context(obj_name, flags, data->sha1, &ctx);
 	if (result != FOUND) {
 		switch (result) {
 		case MISSING_OBJECT:
 			printf("%s missing\n", obj_name);
 			break;
