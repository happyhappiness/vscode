 			       unsigned char repl[20],
 			       int force)
 {
 	unsigned char prev[20];
 	enum object_type obj_type, repl_type;
 	char ref[PATH_MAX];
-	struct ref_lock *lock;
+	struct ref_transaction *transaction;
+	struct strbuf err = STRBUF_INIT;
 
 	obj_type = sha1_object_info(object, NULL);
 	repl_type = sha1_object_info(repl, NULL);
 	if (!force && obj_type != repl_type)
 		die("Objects must be of the same type.\n"
 		    "'%s' points to a replaced object of type '%s'\n"
 		    "while '%s' points to a replacement object of type '%s'.",
 		    object_ref, typename(obj_type),
 		    replace_ref, typename(repl_type));
 
 	check_ref_valid(object, prev, ref, sizeof(ref), force);
 
-	lock = lock_any_ref_for_update(ref, prev, 0, NULL);
-	if (!lock)
-		die("%s: cannot lock the ref", ref);
-	if (write_ref_sha1(lock, repl, NULL) < 0)
-		die("%s: cannot update the ref", ref);
+	transaction = ref_transaction_begin(&err);
+	if (!transaction ||
+	    ref_transaction_update(transaction, ref, repl, prev,
+				   0, 1, NULL, &err) ||
+	    ref_transaction_commit(transaction, &err))
+		die("%s", err.buf);
 
+	ref_transaction_free(transaction);
 	return 0;
 }
 
 static int replace_object(const char *object_ref, const char *replace_ref, int force)
 {
 	unsigned char object[20], repl[20];
