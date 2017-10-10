 		return 1;
 	} else {
 		return 0;
 	}
 }
 
-static void clear_packed_ref_cache(struct ref_cache *refs)
+static void clear_packed_ref_cache(struct files_ref_store *refs)
 {
 	if (refs->packed) {
 		struct packed_ref_cache *packed_refs = refs->packed;
 
 		if (packed_refs->lock)
 			die("internal error: packed-ref cache cleared while locked");
 		refs->packed = NULL;
 		release_packed_ref_cache(packed_refs);
 	}
 }
 
-static void clear_loose_ref_cache(struct ref_cache *refs)
+static void clear_loose_ref_cache(struct files_ref_store *refs)
 {
 	if (refs->loose) {
 		free_ref_entry(refs->loose);
 		refs->loose = NULL;
 	}
 }
 
 /*
  * Create a new submodule ref cache and add it to the internal
  * set of caches.
  */
-static struct ref_cache *create_ref_cache(const char *submodule)
-{
-	struct ref_cache *refs;
-	if (!submodule)
-		submodule = "";
-	FLEX_ALLOC_STR(refs, name, submodule);
-	refs->next = submodule_ref_caches;
-	submodule_ref_caches = refs;
-	return refs;
-}
-
-static struct ref_cache *lookup_ref_cache(const char *submodule)
+static struct ref_store *files_ref_store_create(const char *submodule)
 {
-	struct ref_cache *refs;
+	struct files_ref_store *refs = xcalloc(1, sizeof(*refs));
+	struct ref_store *ref_store = (struct ref_store *)refs;
 
-	if (!submodule || !*submodule)
-		return &ref_cache;
+	base_ref_store_init(ref_store, &refs_be_files, submodule);
 
-	for (refs = submodule_ref_caches; refs; refs = refs->next)
-		if (!strcmp(submodule, refs->name))
-			return refs;
-	return NULL;
+	return ref_store;
 }
 
 /*
- * Return a pointer to a ref_cache for the specified submodule. For
- * the main repository, use submodule==NULL; such a call cannot fail.
- * For a submodule, the submodule must exist and be a nonbare
- * repository, otherwise return NULL.
- *
- * The returned structure will be allocated and initialized but not
- * necessarily populated; it should not be freed.
+ * Downcast ref_store to files_ref_store. Die if ref_store is not a
+ * files_ref_store. If submodule_allowed is not true, then also die if
+ * files_ref_store is for a submodule (i.e., not for the main
+ * repository). caller is used in any necessary error messages.
  */
-static struct ref_cache *get_ref_cache(const char *submodule)
+static struct files_ref_store *files_downcast(
+		struct ref_store *ref_store, int submodule_allowed,
+		const char *caller)
 {
-	struct ref_cache *refs = lookup_ref_cache(submodule);
-
-	if (!refs) {
-		struct strbuf submodule_sb = STRBUF_INIT;
+	if (ref_store->be != &refs_be_files)
+		die("BUG: ref_store is type \"%s\" not \"files\" in %s",
+		    ref_store->be->name, caller);
 
-		strbuf_addstr(&submodule_sb, submodule);
-		if (is_nonbare_repository_dir(&submodule_sb))
-			refs = create_ref_cache(submodule);
-		strbuf_release(&submodule_sb);
-	}
+	if (!submodule_allowed)
+		assert_main_repository(ref_store, caller);
 
-	return refs;
+	return (struct files_ref_store *)ref_store;
 }
 
 /* The length of a peeled reference line in packed-refs, including EOL: */
 #define PEELED_LINE_LENGTH 42
 
 /*
