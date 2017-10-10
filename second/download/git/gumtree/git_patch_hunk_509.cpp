 
 /*
  * Rollback the lockfile for the packed-refs file, and discard the
  * in-memory packed reference cache.  (The packed-refs file will be
  * read anew if it is needed again after this function is called.)
  */
-static void rollback_packed_refs(void)
+static void rollback_packed_refs(struct files_ref_store *refs)
 {
 	struct packed_ref_cache *packed_ref_cache =
-		get_packed_ref_cache(&ref_cache);
+		get_packed_ref_cache(refs);
+
+	assert_main_repository(&refs->base, "rollback_packed_refs");
 
 	if (!packed_ref_cache->lock)
 		die("internal error: packed-refs not locked");
 	rollback_lock_file(packed_ref_cache->lock);
 	packed_ref_cache->lock = NULL;
 	release_packed_ref_cache(packed_ref_cache);
-	clear_packed_ref_cache(&ref_cache);
+	clear_packed_ref_cache(refs);
 }
 
 struct ref_to_prune {
 	struct ref_to_prune *next;
 	unsigned char sha1[20];
 	char name[FLEX_ARRAY];
