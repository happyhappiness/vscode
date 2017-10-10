 
 static void clear_packed_ref_cache(struct files_ref_store *refs)
 {
 	if (refs->packed) {
 		struct packed_ref_cache *packed_refs = refs->packed;
 
-		if (packed_refs->lock)
-			die("internal error: packed-ref cache cleared while locked");
+		if (is_lock_file_locked(&refs->packed_refs_lock))
+			die("BUG: packed-ref cache cleared while locked");
 		refs->packed = NULL;
 		release_packed_ref_cache(packed_refs);
 	}
 }
 
 static void clear_loose_ref_cache(struct files_ref_store *refs)
