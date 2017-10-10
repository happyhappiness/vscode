 	 * to be refactored to allow us to feed a <buffer, size, mode>
 	 * instead of a cache entry.  Such a refactoring would help
 	 * merge_recursive as well (it also writes the merge result to the
 	 * object database even when it may contain conflicts).
 	 */
 	if (write_sha1_file(result_buf.ptr, result_buf.size,
-			    blob_type, sha1))
+			    blob_type, oid.hash))
 		die(_("Unable to add merge result for '%s'"), path);
-	ce = make_cache_entry(mode, sha1, path, 2, 0);
+	ce = make_cache_entry(mode, oid.hash, path, 2, 0);
 	if (!ce)
 		die(_("make_cache_entry failed for path '%s'"), path);
 	status = checkout_entry(ce, state, NULL);
 	return status;
 }
 
 static int checkout_paths(const struct checkout_opts *opts,
 			  const char *revision)
 {
 	int pos;
-	struct checkout state;
+	struct checkout state = CHECKOUT_INIT;
 	static char *ps_matched;
-	unsigned char rev[20];
+	struct object_id rev;
 	struct commit *head;
 	int errs = 0;
 	struct lock_file *lock_file;
 
 	if (opts->track != BRANCH_TRACK_UNSPECIFIED)
 		die(_("'%s' cannot be used with updating paths"), "--track");
