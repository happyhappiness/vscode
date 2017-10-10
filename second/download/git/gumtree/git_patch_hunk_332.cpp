 struct batch_options {
 	int enabled;
 	int follow_symlinks;
 	int print_contents;
 	int buffer_output;
 	int all_objects;
+	int cmdmode; /* may be 'w' or 'c' for --filters or --textconv */
 	const char *format;
 };
 
+static const char *force_path;
+
+static int filter_object(const char *path, unsigned mode,
+			 const struct object_id *oid,
+			 char **buf, unsigned long *size)
+{
+	enum object_type type;
+
+	*buf = read_sha1_file(oid->hash, &type, size);
+	if (!*buf)
+		return error(_("cannot read object %s '%s'"),
+			     oid_to_hex(oid), path);
+	if ((type == OBJ_BLOB) && S_ISREG(mode)) {
+		struct strbuf strbuf = STRBUF_INIT;
+		if (convert_to_working_tree(path, *buf, *size, &strbuf)) {
+			free(*buf);
+			*size = strbuf.len;
+			*buf = strbuf_detach(&strbuf, NULL);
+		}
+	}
+
+	return 0;
+}
+
 static int cat_one_file(int opt, const char *exp_type, const char *obj_name,
 			int unknown_type)
 {
-	unsigned char sha1[20];
+	struct object_id oid;
 	enum object_type type;
 	char *buf;
 	unsigned long size;
 	struct object_context obj_context;
-	struct object_info oi = {NULL};
+	struct object_info oi = OBJECT_INFO_INIT;
 	struct strbuf sb = STRBUF_INIT;
 	unsigned flags = LOOKUP_REPLACE_OBJECT;
+	const char *path = force_path;
 
 	if (unknown_type)
 		flags |= LOOKUP_UNKNOWN_OBJECT;
 
-	if (get_sha1_with_context(obj_name, 0, sha1, &obj_context))
+	if (get_sha1_with_context(obj_name, 0, oid.hash, &obj_context))
 		die("Not a valid object name %s", obj_name);
 
+	if (!path)
+		path = obj_context.path;
+	if (obj_context.mode == S_IFINVALID)
+		obj_context.mode = 0100644;
+
 	buf = NULL;
 	switch (opt) {
 	case 't':
 		oi.typename = &sb;
-		if (sha1_object_info_extended(sha1, &oi, flags) < 0)
+		if (sha1_object_info_extended(oid.hash, &oi, flags) < 0)
 			die("git cat-file: could not get object info");
 		if (sb.len) {
 			printf("%s\n", sb.buf);
 			strbuf_release(&sb);
 			return 0;
 		}
 		break;
 
 	case 's':
 		oi.sizep = &size;
-		if (sha1_object_info_extended(sha1, &oi, flags) < 0)
+		if (sha1_object_info_extended(oid.hash, &oi, flags) < 0)
 			die("git cat-file: could not get object info");
 		printf("%lu\n", size);
 		return 0;
 
 	case 'e':
-		return !has_sha1_file(sha1);
+		return !has_object_file(&oid);
+
+	case 'w':
+		if (!path[0])
+			die("git cat-file --filters %s: <object> must be "
+			    "<sha1:path>", obj_name);
+
+		if (filter_object(path, obj_context.mode,
+				  &oid, &buf, &size))
+			return -1;
+		break;
 
 	case 'c':
-		if (!obj_context.path[0])
+		if (!path[0])
 			die("git cat-file --textconv %s: <object> must be <sha1:path>",
 			    obj_name);
 
-		if (textconv_object(obj_context.path, obj_context.mode, sha1, 1, &buf, &size))
+		if (textconv_object(path, obj_context.mode, &oid, 1, &buf, &size))
 			break;
 
 	case 'p':
-		type = sha1_object_info(sha1, NULL);
+		type = sha1_object_info(oid.hash, NULL);
 		if (type < 0)
 			die("Not a valid object name %s", obj_name);
 
 		/* custom pretty-print here */
 		if (type == OBJ_TREE) {
 			const char *ls_args[3] = { NULL };
 			ls_args[0] =  "ls-tree";
 			ls_args[1] =  obj_name;
 			return cmd_ls_tree(2, ls_args, NULL);
 		}
 
 		if (type == OBJ_BLOB)
-			return stream_blob_to_fd(1, sha1, NULL, 0);
-		buf = read_sha1_file(sha1, &type, &size);
+			return stream_blob_to_fd(1, &oid, NULL, 0);
+		buf = read_sha1_file(oid.hash, &type, &size);
 		if (!buf)
 			die("Cannot read object %s", obj_name);
 
 		/* otherwise just spit out the data */
 		break;
 
 	case 0:
 		if (type_from_string(exp_type) == OBJ_BLOB) {
-			unsigned char blob_sha1[20];
-			if (sha1_object_info(sha1, NULL) == OBJ_TAG) {
-				char *buffer = read_sha1_file(sha1, &type, &size);
+			struct object_id blob_oid;
+			if (sha1_object_info(oid.hash, NULL) == OBJ_TAG) {
+				char *buffer = read_sha1_file(oid.hash, &type, &size);
 				const char *target;
 				if (!skip_prefix(buffer, "object ", &target) ||
-				    get_sha1_hex(target, blob_sha1))
-					die("%s not a valid tag", sha1_to_hex(sha1));
+				    get_oid_hex(target, &blob_oid))
+					die("%s not a valid tag", oid_to_hex(&oid));
 				free(buffer);
 			} else
-				hashcpy(blob_sha1, sha1);
+				oidcpy(&blob_oid, &oid);
 
-			if (sha1_object_info(blob_sha1, NULL) == OBJ_BLOB)
-				return stream_blob_to_fd(1, blob_sha1, NULL, 0);
+			if (sha1_object_info(blob_oid.hash, NULL) == OBJ_BLOB)
+				return stream_blob_to_fd(1, &blob_oid, NULL, 0);
 			/*
 			 * we attempted to dereference a tag to a blob
 			 * and failed; there may be new dereference
 			 * mechanisms this code is not aware of.
 			 * fall-back to the usual case.
 			 */
 		}
-		buf = read_object_with_reference(sha1, exp_type, &size, NULL);
+		buf = read_object_with_reference(oid.hash, exp_type, &size, NULL);
 		break;
 
 	default:
 		die("git cat-file: unknown option: %s", exp_type);
 	}
 
