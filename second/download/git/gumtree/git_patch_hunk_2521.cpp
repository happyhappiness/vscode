 #define DIRENT_SORT_HINT(de) 0
 #else
 #define SORT_DIRENT 1
 #define DIRENT_SORT_HINT(de) ((de)->d_ino)
 #endif
 
-static void objreport(struct object *obj, const char *severity,
-                      const char *err, va_list params)
+static int fsck_config(const char *var, const char *value, void *cb)
 {
-	fprintf(stderr, "%s in %s %s: ",
-	        severity, typename(obj->type), sha1_to_hex(obj->sha1));
-	vfprintf(stderr, err, params);
-	fputs("\n", stderr);
+	if (strcmp(var, "fsck.skiplist") == 0) {
+		const char *path;
+		struct strbuf sb = STRBUF_INIT;
+
+		if (git_config_pathname(&path, var, value))
+			return 1;
+		strbuf_addf(&sb, "skiplist=%s", path);
+		free((char *)path);
+		fsck_set_msg_types(&fsck_obj_options, sb.buf);
+		strbuf_release(&sb);
+		return 0;
+	}
+
+	if (skip_prefix(var, "fsck.", &var)) {
+		fsck_set_msg_type(&fsck_obj_options, var, value);
+		return 0;
+	}
+
+	return git_default_config(var, value, cb);
+}
+
+static void objreport(struct object *obj, const char *msg_type,
+			const char *err)
+{
+	fprintf(stderr, "%s in %s %s: %s\n",
+		msg_type, typename(obj->type), sha1_to_hex(obj->sha1), err);
 }
 
-__attribute__((format (printf, 2, 3)))
-static int objerror(struct object *obj, const char *err, ...)
+static int objerror(struct object *obj, const char *err)
 {
-	va_list params;
-	va_start(params, err);
 	errors_found |= ERROR_OBJECT;
-	objreport(obj, "error", err, params);
-	va_end(params);
+	objreport(obj, "error", err);
 	return -1;
 }
 
-__attribute__((format (printf, 3, 4)))
-static int fsck_error_func(struct object *obj, int type, const char *err, ...)
+static int fsck_error_func(struct object *obj, int type, const char *message)
 {
-	va_list params;
-	va_start(params, err);
-	objreport(obj, (type == FSCK_WARN) ? "warning" : "error", err, params);
-	va_end(params);
+	objreport(obj, (type == FSCK_WARN) ? "warning" : "error", message);
 	return (type == FSCK_WARN) ? 0 : 1;
 }
 
 static struct object_array pending;
 
-static int mark_object(struct object *obj, int type, void *data)
+static int mark_object(struct object *obj, int type, void *data, struct fsck_options *options)
 {
 	struct object *parent = data;
 
 	/*
 	 * The only case data is NULL or type is OBJ_ANY is when
 	 * mark_object_reachable() calls us.  All the callers of
