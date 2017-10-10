 {
 	enum peel_status peel_status = peel_entry(entry, 0);
 
 	if (peel_status != PEEL_PEELED && peel_status != PEEL_NON_TAG)
 		error("internal error: %s is not a valid packed reference!",
 		      entry->name);
-	write_packed_entry(cb_data, entry->name, entry->u.value.sha1,
+	write_packed_entry(cb_data, entry->name, entry->u.value.oid.hash,
 			   peel_status == PEEL_PEELED ?
-			   entry->u.value.peeled : NULL);
+			   entry->u.value.peeled.hash : NULL);
 	return 0;
 }
 
 /* This should return a meaningful errno on failure */
 int lock_packed_refs(int flags)
 {
+	static int timeout_configured = 0;
+	static int timeout_value = 1000;
+
 	struct packed_ref_cache *packed_ref_cache;
 
-	if (hold_lock_file_for_update(&packlock, git_path("packed-refs"), flags) < 0)
+	if (!timeout_configured) {
+		git_config_get_int("core.packedrefstimeout", &timeout_value);
+		timeout_configured = 1;
+	}
+
+	if (hold_lock_file_for_update_timeout(
+			    &packlock, git_path("packed-refs"),
+			    flags, timeout_value) < 0)
 		return -1;
 	/*
 	 * Get the current packed-refs while holding the lock.  If the
 	 * packed-refs file has been modified since we last read it,
 	 * this will automatically invalidate the cache and re-read
 	 * the packed-refs file.
