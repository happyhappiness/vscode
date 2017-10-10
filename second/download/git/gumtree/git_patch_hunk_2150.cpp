 		die_errno("unable to overwrite old ref-pack file");
 
 	prune_refs(cbdata.ref_to_prune);
 	return 0;
 }
 
-/*
- * If entry is no longer needed in packed-refs, add it to the string
- * list pointed to by cb_data.  Reasons for deleting entries:
- *
- * - Entry is broken.
- * - Entry is overridden by a loose ref.
- * - Entry does not point at a valid object.
- *
- * In the first and third cases, also emit an error message because these
- * are indications of repository corruption.
- */
-static int curate_packed_ref_fn(struct ref_entry *entry, void *cb_data)
-{
-	struct string_list *refs_to_delete = cb_data;
-
-	if (entry->flag & REF_ISBROKEN) {
-		/* This shouldn't happen to packed refs. */
-		error("%s is broken!", entry->name);
-		string_list_append(refs_to_delete, entry->name);
-		return 0;
-	}
-	if (!has_sha1_file(entry->u.value.sha1)) {
-		unsigned char sha1[20];
-		int flags;
-
-		if (read_ref_full(entry->name, 0, sha1, &flags))
-			/* We should at least have found the packed ref. */
-			die("Internal error");
-		if ((flags & REF_ISSYMREF) || !(flags & REF_ISPACKED)) {
-			/*
-			 * This packed reference is overridden by a
-			 * loose reference, so it is OK that its value
-			 * is no longer valid; for example, it might
-			 * refer to an object that has been garbage
-			 * collected.  For this purpose we don't even
-			 * care whether the loose reference itself is
-			 * invalid, broken, symbolic, etc.  Silently
-			 * remove the packed reference.
-			 */
-			string_list_append(refs_to_delete, entry->name);
-			return 0;
-		}
-		/*
-		 * There is no overriding loose reference, so the fact
-		 * that this reference doesn't refer to a valid object
-		 * indicates some kind of repository corruption.
-		 * Report the problem, then omit the reference from
-		 * the output.
-		 */
-		error("%s does not point to a valid object!", entry->name);
-		string_list_append(refs_to_delete, entry->name);
-		return 0;
-	}
-
-	return 0;
-}
-
 int repack_without_refs(struct string_list *refnames, struct strbuf *err)
 {
 	struct ref_dir *packed;
-	struct string_list refs_to_delete = STRING_LIST_INIT_DUP;
-	struct string_list_item *refname, *ref_to_delete;
+	struct string_list_item *refname;
 	int ret, needs_repacking = 0, removed = 0;
 
 	assert(err);
 
 	/* Look for a packed ref */
 	for_each_string_list_item(refname, refnames) {
