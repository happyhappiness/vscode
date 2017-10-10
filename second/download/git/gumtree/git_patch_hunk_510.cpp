 	while (r) {
 		prune_ref(r);
 		r = r->next;
 	}
 }
 
-int pack_refs(unsigned int flags)
+static int files_pack_refs(struct ref_store *ref_store, unsigned int flags)
 {
+	struct files_ref_store *refs =
+		files_downcast(ref_store, 0, "pack_refs");
 	struct pack_refs_cb_data cbdata;
 
 	memset(&cbdata, 0, sizeof(cbdata));
 	cbdata.flags = flags;
 
-	lock_packed_refs(LOCK_DIE_ON_ERROR);
-	cbdata.packed_refs = get_packed_refs(&ref_cache);
+	lock_packed_refs(refs, LOCK_DIE_ON_ERROR);
+	cbdata.packed_refs = get_packed_refs(refs);
 
-	do_for_each_entry_in_dir(get_loose_refs(&ref_cache), 0,
+	do_for_each_entry_in_dir(get_loose_refs(refs), 0,
 				 pack_if_possible_fn, &cbdata);
 
-	if (commit_packed_refs())
+	if (commit_packed_refs(refs))
 		die_errno("unable to overwrite old ref-pack file");
 
 	prune_refs(cbdata.ref_to_prune);
 	return 0;
 }
 
