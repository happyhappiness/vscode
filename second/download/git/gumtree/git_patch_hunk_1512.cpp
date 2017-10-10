  * Add a reference to the in-memory packed reference cache.  This may
  * only be called while the packed-refs file is locked (see
  * lock_packed_refs()).  To actually write the packed-refs file, call
  * commit_packed_refs().
  */
 static void add_packed_ref(struct files_ref_store *refs,
-			   const char *refname, const unsigned char *sha1)
+			   const char *refname, const struct object_id *oid)
 {
 	struct packed_ref_cache *packed_ref_cache = get_packed_ref_cache(refs);
 
-	if (!packed_ref_cache->lock)
-		die("internal error: packed refs not locked");
+	if (!is_lock_file_locked(&refs->packed_refs_lock))
+		die("BUG: packed refs not locked");
+
+	if (check_refname_format(refname, REFNAME_ALLOW_ONELEVEL))
+		die("Reference has invalid format: '%s'", refname);
+
 	add_ref_entry(get_packed_ref_dir(packed_ref_cache),
-		      create_ref_entry(refname, sha1, REF_ISPACKED, 1));
+		      create_ref_entry(refname, oid, REF_ISPACKED));
 }
 
 /*
  * Read the loose references from the namespace dirname into dir
  * (without recursing).  dirname must end with '/'.  dir must be the
  * directory entry corresponding to dirname.
