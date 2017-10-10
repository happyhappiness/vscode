 		die_errno("unable to overwrite old ref-pack file");
 
 	prune_refs(cbdata.ref_to_prune);
 	return 0;
 }
 
-int repack_without_refs(struct string_list *refnames, struct strbuf *err)
+/*
+ * Rewrite the packed-refs file, omitting any refs listed in
+ * 'refnames'. On error, leave packed-refs unchanged, write an error
+ * message to 'err', and return a nonzero value.
+ *
+ * The refs in 'refnames' needn't be sorted. `err` must not be NULL.
+ */
+static int repack_without_refs(struct string_list *refnames, struct strbuf *err)
 {
 	struct ref_dir *packed;
 	struct string_list_item *refname;
 	int ret, needs_repacking = 0, removed = 0;
 
 	assert(err);
