 					  len - strlen("encoding \n"),
 					  encoding, strlen(encoding));
 	}
 	return strbuf_detach(&tmp, NULL);
 }
 
-char *logmsg_reencode(const struct commit *commit,
-		      char **commit_encoding,
-		      const char *output_encoding)
+const char *logmsg_reencode(const struct commit *commit,
+			    char **commit_encoding,
+			    const char *output_encoding)
 {
 	static const char *utf8 = "UTF-8";
 	const char *use_encoding;
 	char *encoding;
-	char *msg = commit->buffer;
+	const char *msg = get_commit_buffer(commit, NULL);
 	char *out;
 
-	if (!msg) {
-		enum object_type type;
-		unsigned long size;
-
-		msg = read_sha1_file(commit->object.sha1, &type, &size);
-		if (!msg)
-			die("Cannot read commit object %s",
-			    sha1_to_hex(commit->object.sha1));
-		if (type != OBJ_COMMIT)
-			die("Expected commit for '%s', got %s",
-			    sha1_to_hex(commit->object.sha1), typename(type));
-	}
-
 	if (!output_encoding || !*output_encoding) {
 		if (commit_encoding)
 			*commit_encoding =
 				get_header(commit, msg, "encoding");
 		return msg;
 	}
