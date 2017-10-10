 	else {
 		enum object_type type;
 
 		buffer = to_free =
 			read_sha1_file(tag->object.sha1, &type, &size);
 		if (!buffer)
-			return error_func(&tag->object, FSCK_ERROR,
+			return report(options, &tag->object,
+				FSCK_MSG_MISSING_TAG_OBJECT,
 				"cannot read tag object");
 
 		if (type != OBJ_TAG) {
-			ret = error_func(&tag->object, FSCK_ERROR,
+			ret = report(options, &tag->object,
+				FSCK_MSG_TAG_OBJECT_NOT_TAG,
 				"expected tag got %s",
 			    typename(type));
 			goto done;
 		}
 	}
 
-	if (verify_headers(buffer, size, &tag->object, error_func))
+	if (verify_headers(buffer, size, &tag->object, options))
 		goto done;
 
 	if (!skip_prefix(buffer, "object ", &buffer)) {
-		ret = error_func(&tag->object, FSCK_ERROR, "invalid format - expected 'object' line");
+		ret = report(options, &tag->object, FSCK_MSG_MISSING_OBJECT, "invalid format - expected 'object' line");
 		goto done;
 	}
 	if (get_sha1_hex(buffer, sha1) || buffer[40] != '\n') {
-		ret = error_func(&tag->object, FSCK_ERROR, "invalid 'object' line format - bad sha1");
-		goto done;
+		ret = report(options, &tag->object, FSCK_MSG_BAD_OBJECT_SHA1, "invalid 'object' line format - bad sha1");
+		if (ret)
+			goto done;
 	}
 	buffer += 41;
 
 	if (!skip_prefix(buffer, "type ", &buffer)) {
-		ret = error_func(&tag->object, FSCK_ERROR, "invalid format - expected 'type' line");
+		ret = report(options, &tag->object, FSCK_MSG_MISSING_TYPE_ENTRY, "invalid format - expected 'type' line");
 		goto done;
 	}
 	eol = strchr(buffer, '\n');
 	if (!eol) {
-		ret = error_func(&tag->object, FSCK_ERROR, "invalid format - unexpected end after 'type' line");
+		ret = report(options, &tag->object, FSCK_MSG_MISSING_TYPE, "invalid format - unexpected end after 'type' line");
 		goto done;
 	}
 	if (type_from_string_gently(buffer, eol - buffer, 1) < 0)
-		ret = error_func(&tag->object, FSCK_ERROR, "invalid 'type' value");
+		ret = report(options, &tag->object, FSCK_MSG_BAD_TYPE, "invalid 'type' value");
 	if (ret)
 		goto done;
 	buffer = eol + 1;
 
 	if (!skip_prefix(buffer, "tag ", &buffer)) {
-		ret = error_func(&tag->object, FSCK_ERROR, "invalid format - expected 'tag' line");
+		ret = report(options, &tag->object, FSCK_MSG_MISSING_TAG_ENTRY, "invalid format - expected 'tag' line");
 		goto done;
 	}
 	eol = strchr(buffer, '\n');
 	if (!eol) {
-		ret = error_func(&tag->object, FSCK_ERROR, "invalid format - unexpected end after 'type' line");
+		ret = report(options, &tag->object, FSCK_MSG_MISSING_TAG, "invalid format - unexpected end after 'type' line");
 		goto done;
 	}
 	strbuf_addf(&sb, "refs/tags/%.*s", (int)(eol - buffer), buffer);
-	if (check_refname_format(sb.buf, 0))
-		error_func(&tag->object, FSCK_WARN, "invalid 'tag' name: %.*s",
+	if (check_refname_format(sb.buf, 0)) {
+		ret = report(options, &tag->object, FSCK_MSG_BAD_TAG_NAME,
+			   "invalid 'tag' name: %.*s",
 			   (int)(eol - buffer), buffer);
+		if (ret)
+			goto done;
+	}
 	buffer = eol + 1;
 
-	if (!skip_prefix(buffer, "tagger ", &buffer))
+	if (!skip_prefix(buffer, "tagger ", &buffer)) {
 		/* early tags do not contain 'tagger' lines; warn only */
-		error_func(&tag->object, FSCK_WARN, "invalid format - expected 'tagger' line");
+		ret = report(options, &tag->object, FSCK_MSG_MISSING_TAGGER_ENTRY, "invalid format - expected 'tagger' line");
+		if (ret)
+			goto done;
+	}
 	else
-		ret = fsck_ident(&buffer, &tag->object, error_func);
+		ret = fsck_ident(&buffer, &tag->object, options);
 
 done:
 	strbuf_release(&sb);
 	free(to_free);
 	return ret;
 }
 
 static int fsck_tag(struct tag *tag, const char *data,
-	unsigned long size, fsck_error error_func)
+	unsigned long size, struct fsck_options *options)
 {
 	struct object *tagged = tag->tagged;
 
 	if (!tagged)
-		return error_func(&tag->object, FSCK_ERROR, "could not load tagged object");
+		return report(options, &tag->object, FSCK_MSG_BAD_TAG_OBJECT, "could not load tagged object");
 
-	return fsck_tag_buffer(tag, data, size, error_func);
+	return fsck_tag_buffer(tag, data, size, options);
 }
 
 int fsck_object(struct object *obj, void *data, unsigned long size,
-	int strict, fsck_error error_func)
+	struct fsck_options *options)
 {
 	if (!obj)
-		return error_func(obj, FSCK_ERROR, "no valid object to fsck");
+		return report(options, obj, FSCK_MSG_BAD_OBJECT_SHA1, "no valid object to fsck");
 
 	if (obj->type == OBJ_BLOB)
 		return 0;
 	if (obj->type == OBJ_TREE)
-		return fsck_tree((struct tree *) obj, strict, error_func);
+		return fsck_tree((struct tree *) obj, options);
 	if (obj->type == OBJ_COMMIT)
 		return fsck_commit((struct commit *) obj, (const char *) data,
-			size, error_func);
+			size, options);
 	if (obj->type == OBJ_TAG)
 		return fsck_tag((struct tag *) obj, (const char *) data,
-			size, error_func);
+			size, options);
 
-	return error_func(obj, FSCK_ERROR, "unknown type '%d' (internal fsck error)",
+	return report(options, obj, FSCK_MSG_UNKNOWN_TYPE, "unknown type '%d' (internal fsck error)",
 			  obj->type);
 }
 
-int fsck_error_function(struct object *obj, int type, const char *fmt, ...)
+int fsck_error_function(struct object *obj, int msg_type, const char *message)
 {
-	va_list ap;
-	struct strbuf sb = STRBUF_INIT;
-
-	strbuf_addf(&sb, "object %s:", sha1_to_hex(obj->sha1));
-
-	va_start(ap, fmt);
-	strbuf_vaddf(&sb, fmt, ap);
-	va_end(ap);
-
-	error("%s", sb.buf);
-	strbuf_release(&sb);
+	if (msg_type == FSCK_WARN) {
+		warning("object %s: %s", sha1_to_hex(obj->sha1), message);
+		return 0;
+	}
+	error("object %s: %s", sha1_to_hex(obj->sha1), message);
 	return 1;
 }
