 	for_each_replace_ref(show_reference, (void *)&data);
 
 	return 0;
 }
 
 typedef int (*each_replace_name_fn)(const char *name, const char *ref,
-				    const unsigned char *sha1);
+				    const struct object_id *oid);
 
 static int for_each_replace_name(const char **argv, each_replace_name_fn fn)
 {
 	const char **p, *full_hex;
-	char ref[PATH_MAX];
+	struct strbuf ref = STRBUF_INIT;
+	size_t base_len;
 	int had_error = 0;
-	unsigned char sha1[20];
+	struct object_id oid;
+
+	strbuf_addstr(&ref, git_replace_ref_base);
+	base_len = ref.len;
 
 	for (p = argv; *p; p++) {
-		if (get_sha1(*p, sha1)) {
+		if (get_oid(*p, &oid)) {
 			error("Failed to resolve '%s' as a valid ref.", *p);
 			had_error = 1;
 			continue;
 		}
-		full_hex = sha1_to_hex(sha1);
-		snprintf(ref, sizeof(ref), "%s%s", git_replace_ref_base, full_hex);
-		/* read_ref() may reuse the buffer */
-		full_hex = ref + strlen(git_replace_ref_base);
-		if (read_ref(ref, sha1)) {
+
+		strbuf_setlen(&ref, base_len);
+		strbuf_addstr(&ref, oid_to_hex(&oid));
+		full_hex = ref.buf + base_len;
+
+		if (read_ref(ref.buf, oid.hash)) {
 			error("replace ref '%s' not found.", full_hex);
 			had_error = 1;
 			continue;
 		}
-		if (fn(full_hex, ref, sha1))
+		if (fn(full_hex, ref.buf, &oid))
 			had_error = 1;
 	}
+	strbuf_release(&ref);
 	return had_error;
 }
 
 static int delete_replace_ref(const char *name, const char *ref,
-			      const unsigned char *sha1)
+			      const struct object_id *oid)
 {
-	if (delete_ref(ref, sha1, 0))
+	if (delete_ref(NULL, ref, oid->hash, 0))
 		return 1;
 	printf("Deleted replace ref '%s'\n", name);
 	return 0;
 }
 
-static void check_ref_valid(unsigned char object[20],
-			    unsigned char prev[20],
-			    char *ref,
-			    int ref_size,
+static void check_ref_valid(struct object_id *object,
+			    struct object_id *prev,
+			    struct strbuf *ref,
 			    int force)
 {
-	if (snprintf(ref, ref_size,
-		     "%s%s", git_replace_ref_base,
-		     sha1_to_hex(object)) > ref_size - 1)
-		die("replace ref name too long: %.*s...", 50, ref);
-	if (check_refname_format(ref, 0))
-		die("'%s' is not a valid ref name.", ref);
+	strbuf_reset(ref);
+	strbuf_addf(ref, "%s%s", git_replace_ref_base, oid_to_hex(object));
+	if (check_refname_format(ref->buf, 0))
+		die("'%s' is not a valid ref name.", ref->buf);
 
-	if (read_ref(ref, prev))
-		hashclr(prev);
+	if (read_ref(ref->buf, prev->hash))
+		oidclr(prev);
 	else if (!force)
-		die("replace ref '%s' already exists", ref);
+		die("replace ref '%s' already exists", ref->buf);
 }
 
-static int replace_object_sha1(const char *object_ref,
-			       unsigned char object[20],
+static int replace_object_oid(const char *object_ref,
+			       struct object_id *object,
 			       const char *replace_ref,
-			       unsigned char repl[20],
+			       struct object_id *repl,
 			       int force)
 {
-	unsigned char prev[20];
+	struct object_id prev;
 	enum object_type obj_type, repl_type;
-	char ref[PATH_MAX];
+	struct strbuf ref = STRBUF_INIT;
 	struct ref_transaction *transaction;
 	struct strbuf err = STRBUF_INIT;
 
-	obj_type = sha1_object_info(object, NULL);
-	repl_type = sha1_object_info(repl, NULL);
+	obj_type = sha1_object_info(object->hash, NULL);
+	repl_type = sha1_object_info(repl->hash, NULL);
 	if (!force && obj_type != repl_type)
 		die("Objects must be of the same type.\n"
 		    "'%s' points to a replaced object of type '%s'\n"
 		    "while '%s' points to a replacement object of type '%s'.",
 		    object_ref, typename(obj_type),
 		    replace_ref, typename(repl_type));
 
-	check_ref_valid(object, prev, ref, sizeof(ref), force);
+	check_ref_valid(object, &prev, &ref, force);
 
 	transaction = ref_transaction_begin(&err);
 	if (!transaction ||
-	    ref_transaction_update(transaction, ref, repl, prev,
+	    ref_transaction_update(transaction, ref.buf, repl->hash, prev.hash,
 				   0, NULL, &err) ||
 	    ref_transaction_commit(transaction, &err))
 		die("%s", err.buf);
 
 	ref_transaction_free(transaction);
+	strbuf_release(&ref);
 	return 0;
 }
 
 static int replace_object(const char *object_ref, const char *replace_ref, int force)
 {
-	unsigned char object[20], repl[20];
+	struct object_id object, repl;
 
-	if (get_sha1(object_ref, object))
+	if (get_oid(object_ref, &object))
 		die("Failed to resolve '%s' as a valid ref.", object_ref);
-	if (get_sha1(replace_ref, repl))
+	if (get_oid(replace_ref, &repl))
 		die("Failed to resolve '%s' as a valid ref.", replace_ref);
 
-	return replace_object_sha1(object_ref, object, replace_ref, repl, force);
+	return replace_object_oid(object_ref, &object, replace_ref, &repl, force);
 }
 
 /*
  * Write the contents of the object named by "sha1" to the file "filename".
  * If "raw" is true, then the object's raw contents are printed according to
  * "type". Otherwise, we pretty-print the contents for human editing.
  */
-static void export_object(const unsigned char *sha1, enum object_type type,
+static void export_object(const struct object_id *oid, enum object_type type,
 			  int raw, const char *filename)
 {
 	struct child_process cmd = CHILD_PROCESS_INIT;
 	int fd;
 
 	fd = open(filename, O_WRONLY | O_CREAT | O_TRUNC, 0666);
