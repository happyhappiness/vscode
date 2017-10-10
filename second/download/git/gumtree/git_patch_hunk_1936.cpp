 	}
 }
 
 int walker_fetch(struct walker *walker, int targets, char **target,
 		 const char **write_ref, const char *write_ref_log_details)
 {
-	struct ref_lock **lock = xcalloc(targets, sizeof(struct ref_lock *));
+	struct strbuf refname = STRBUF_INIT;
+	struct strbuf err = STRBUF_INIT;
+	struct ref_transaction *transaction = NULL;
 	unsigned char *sha1 = xmalloc(targets * 20);
-	const char *msg;
-	char *to_free = NULL;
-	int ret;
-	int i;
+	char *msg = NULL;
+	int i, ret = -1;
 
 	save_commit_buffer = 0;
 
-	for (i = 0; i < targets; i++) {
-		if (!write_ref || !write_ref[i])
-			continue;
-
-		lock[i] = lock_ref_sha1(write_ref[i], NULL);
-		if (!lock[i]) {
-			error("Can't lock ref %s", write_ref[i]);
-			goto unlock_and_fail;
+	if (write_ref) {
+		transaction = ref_transaction_begin(&err);
+		if (!transaction) {
+			error("%s", err.buf);
+			goto done;
 		}
 	}
 
-	if (!walker->get_recover)
+	if (!walker->get_recover) {
 		for_each_ref(mark_complete, NULL);
+		commit_list_sort_by_date(&complete);
+	}
 
 	for (i = 0; i < targets; i++) {
 		if (interpret_target(walker, target[i], &sha1[20 * i])) {
 			error("Could not interpret response from server '%s' as something to pull", target[i]);
-			goto unlock_and_fail;
+			goto done;
 		}
 		if (process(walker, lookup_unknown_object(&sha1[20 * i])))
-			goto unlock_and_fail;
+			goto done;
 	}
 
 	if (loop(walker))
-		goto unlock_and_fail;
-
-	if (write_ref_log_details)
-		msg = to_free = xstrfmt("fetch from %s", write_ref_log_details);
-	else
-		msg = "fetch (unknown)";
+		goto done;
+	if (!write_ref) {
+		ret = 0;
+		goto done;
+	}
+	if (write_ref_log_details) {
+		msg = xstrfmt("fetch from %s", write_ref_log_details);
+	} else {
+		msg = NULL;
+	}
 	for (i = 0; i < targets; i++) {
-		if (!write_ref || !write_ref[i])
+		if (!write_ref[i])
 			continue;
-		ret = write_ref_sha1(lock[i], &sha1[20 * i], msg);
-		lock[i] = NULL;
-		if (ret)
-			goto unlock_and_fail;
+		strbuf_reset(&refname);
+		strbuf_addf(&refname, "refs/%s", write_ref[i]);
+		if (ref_transaction_update(transaction, refname.buf,
+					   &sha1[20 * i], NULL, 0, 0,
+					   msg ? msg : "fetch (unknown)",
+					   &err)) {
+			error("%s", err.buf);
+			goto done;
+		}
+	}
+	if (ref_transaction_commit(transaction, &err)) {
+		error("%s", err.buf);
+		goto done;
 	}
-	free(to_free);
-
-	return 0;
-
-unlock_and_fail:
-	for (i = 0; i < targets; i++)
-		if (lock[i])
-			unlock_ref(lock[i]);
-	free(to_free);
 
-	return -1;
+	ret = 0;
+
+done:
+	ref_transaction_free(transaction);
+	free(msg);
+	free(sha1);
+	strbuf_release(&err);
+	strbuf_release(&refname);
+	return ret;
 }
 
 void walker_free(struct walker *walker)
 {
 	walker->cleanup(walker);
 	free(walker);
