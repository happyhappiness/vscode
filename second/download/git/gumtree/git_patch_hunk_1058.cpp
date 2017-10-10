 struct ref_to_prune {
 	struct ref_to_prune *next;
 	unsigned char sha1[20];
 	char name[FLEX_ARRAY];
 };
 
-struct pack_refs_cb_data {
-	unsigned int flags;
-	struct ref_dir *packed_refs;
-	struct ref_to_prune *ref_to_prune;
+enum {
+	REMOVE_EMPTY_PARENTS_REF = 0x01,
+	REMOVE_EMPTY_PARENTS_REFLOG = 0x02
 };
 
 /*
- * An each_ref_entry_fn that is run over loose references only.  If
- * the loose reference can be packed, add an entry in the packed ref
- * cache.  If the reference should be pruned, also add it to
- * ref_to_prune in the pack_refs_cb_data.
- */
-static int pack_if_possible_fn(struct ref_entry *entry, void *cb_data)
-{
-	struct pack_refs_cb_data *cb = cb_data;
-	enum peel_status peel_status;
-	struct ref_entry *packed_entry;
-	int is_tag_ref = starts_with(entry->name, "refs/tags/");
-
-	/* Do not pack per-worktree refs: */
-	if (ref_type(entry->name) != REF_TYPE_NORMAL)
-		return 0;
-
-	/* ALWAYS pack tags */
-	if (!(cb->flags & PACK_REFS_ALL) && !is_tag_ref)
-		return 0;
-
-	/* Do not pack symbolic or broken refs: */
-	if ((entry->flag & REF_ISSYMREF) || !entry_resolves_to_object(entry))
-		return 0;
-
-	/* Add a packed ref cache entry equivalent to the loose entry. */
-	peel_status = peel_entry(entry, 1);
-	if (peel_status != PEEL_PEELED && peel_status != PEEL_NON_TAG)
-		die("internal error peeling reference %s (%s)",
-		    entry->name, oid_to_hex(&entry->u.value.oid));
-	packed_entry = find_ref(cb->packed_refs, entry->name);
-	if (packed_entry) {
-		/* Overwrite existing packed entry with info from loose entry */
-		packed_entry->flag = REF_ISPACKED | REF_KNOWS_PEELED;
-		oidcpy(&packed_entry->u.value.oid, &entry->u.value.oid);
-	} else {
-		packed_entry = create_ref_entry(entry->name, entry->u.value.oid.hash,
-						REF_ISPACKED | REF_KNOWS_PEELED, 0);
-		add_ref(cb->packed_refs, packed_entry);
-	}
-	oidcpy(&packed_entry->u.value.peeled, &entry->u.value.peeled);
-
-	/* Schedule the loose reference for pruning if requested. */
-	if ((cb->flags & PACK_REFS_PRUNE)) {
-		struct ref_to_prune *n;
-		FLEX_ALLOC_STR(n, name, entry->name);
-		hashcpy(n->sha1, entry->u.value.oid.hash);
-		n->next = cb->ref_to_prune;
-		cb->ref_to_prune = n;
-	}
-	return 0;
-}
-
-/*
- * Remove empty parents, but spare refs/ and immediate subdirs.
- * Note: munges *name.
+ * Remove empty parent directories associated with the specified
+ * reference and/or its reflog, but spare [logs/]refs/ and immediate
+ * subdirs. flags is a combination of REMOVE_EMPTY_PARENTS_REF and/or
+ * REMOVE_EMPTY_PARENTS_REFLOG.
  */
-static void try_remove_empty_parents(char *name)
+static void try_remove_empty_parents(struct files_ref_store *refs,
+				     const char *refname,
+				     unsigned int flags)
 {
+	struct strbuf buf = STRBUF_INIT;
+	struct strbuf sb = STRBUF_INIT;
 	char *p, *q;
 	int i;
-	p = name;
+
+	strbuf_addstr(&buf, refname);
+	p = buf.buf;
 	for (i = 0; i < 2; i++) { /* refs/{heads,tags,...}/ */
 		while (*p && *p != '/')
 			p++;
 		/* tolerate duplicate slashes; see check_refname_format() */
 		while (*p == '/')
 			p++;
 	}
-	for (q = p; *q; q++)
-		;
-	while (1) {
+	q = buf.buf + buf.len;
+	while (flags & (REMOVE_EMPTY_PARENTS_REF | REMOVE_EMPTY_PARENTS_REFLOG)) {
 		while (q > p && *q != '/')
 			q--;
 		while (q > p && *(q-1) == '/')
 			q--;
 		if (q == p)
 			break;
-		*q = '\0';
-		if (rmdir(git_path("%s", name)))
-			break;
+		strbuf_setlen(&buf, q - buf.buf);
+
+		strbuf_reset(&sb);
+		files_ref_path(refs, &sb, buf.buf);
+		if ((flags & REMOVE_EMPTY_PARENTS_REF) && rmdir(sb.buf))
+			flags &= ~REMOVE_EMPTY_PARENTS_REF;
+
+		strbuf_reset(&sb);
+		files_reflog_path(refs, &sb, buf.buf);
+		if ((flags & REMOVE_EMPTY_PARENTS_REFLOG) && rmdir(sb.buf))
+			flags &= ~REMOVE_EMPTY_PARENTS_REFLOG;
 	}
+	strbuf_release(&buf);
+	strbuf_release(&sb);
 }
 
 /* make sure nobody touched the ref, and unlink */
-static void prune_ref(struct ref_to_prune *r)
+static void prune_ref(struct files_ref_store *refs, struct ref_to_prune *r)
 {
 	struct ref_transaction *transaction;
 	struct strbuf err = STRBUF_INIT;
 
 	if (check_refname_format(r->name, 0))
 		return;
 
-	transaction = ref_transaction_begin(&err);
+	transaction = ref_store_transaction_begin(&refs->base, &err);
 	if (!transaction ||
 	    ref_transaction_delete(transaction, r->name, r->sha1,
 				   REF_ISPRUNING | REF_NODEREF, NULL, &err) ||
 	    ref_transaction_commit(transaction, &err)) {
 		ref_transaction_free(transaction);
 		error("%s", err.buf);
 		strbuf_release(&err);
 		return;
 	}
 	ref_transaction_free(transaction);
 	strbuf_release(&err);
-	try_remove_empty_parents(r->name);
 }
 
-static void prune_refs(struct ref_to_prune *r)
+static void prune_refs(struct files_ref_store *refs, struct ref_to_prune *r)
 {
 	while (r) {
-		prune_ref(r);
+		prune_ref(refs, r);
 		r = r->next;
 	}
 }
 
 static int files_pack_refs(struct ref_store *ref_store, unsigned int flags)
 {
 	struct files_ref_store *refs =
-		files_downcast(ref_store, 0, "pack_refs");
-	struct pack_refs_cb_data cbdata;
-
-	memset(&cbdata, 0, sizeof(cbdata));
-	cbdata.flags = flags;
+		files_downcast(ref_store, REF_STORE_WRITE | REF_STORE_ODB,
+			       "pack_refs");
+	struct ref_iterator *iter;
+	struct ref_dir *packed_refs;
+	int ok;
+	struct ref_to_prune *refs_to_prune = NULL;
 
 	lock_packed_refs(refs, LOCK_DIE_ON_ERROR);
-	cbdata.packed_refs = get_packed_refs(refs);
+	packed_refs = get_packed_refs(refs);
+
+	iter = cache_ref_iterator_begin(get_loose_ref_cache(refs), NULL, 0);
+	while ((ok = ref_iterator_advance(iter)) == ITER_OK) {
+		/*
+		 * If the loose reference can be packed, add an entry
+		 * in the packed ref cache. If the reference should be
+		 * pruned, also add it to refs_to_prune.
+		 */
+		struct ref_entry *packed_entry;
+		int is_tag_ref = starts_with(iter->refname, "refs/tags/");
+
+		/* Do not pack per-worktree refs: */
+		if (ref_type(iter->refname) != REF_TYPE_NORMAL)
+			continue;
+
+		/* ALWAYS pack tags */
+		if (!(flags & PACK_REFS_ALL) && !is_tag_ref)
+			continue;
+
+		/* Do not pack symbolic or broken refs: */
+		if (iter->flags & REF_ISSYMREF)
+			continue;
+
+		if (!ref_resolves_to_object(iter->refname, iter->oid, iter->flags))
+			continue;
 
-	do_for_each_entry_in_dir(get_loose_refs(refs), 0,
-				 pack_if_possible_fn, &cbdata);
+		/*
+		 * Create an entry in the packed-refs cache equivalent
+		 * to the one from the loose ref cache, except that
+		 * we don't copy the peeled status, because we want it
+		 * to be re-peeled.
+		 */
+		packed_entry = find_ref_entry(packed_refs, iter->refname);
+		if (packed_entry) {
+			/* Overwrite existing packed entry with info from loose entry */
+			packed_entry->flag = REF_ISPACKED;
+			oidcpy(&packed_entry->u.value.oid, iter->oid);
+		} else {
+			packed_entry = create_ref_entry(iter->refname, iter->oid->hash,
+							REF_ISPACKED, 0);
+			add_ref_entry(packed_refs, packed_entry);
+		}
+		oidclr(&packed_entry->u.value.peeled);
+
+		/* Schedule the loose reference for pruning if requested. */
+		if ((flags & PACK_REFS_PRUNE)) {
+			struct ref_to_prune *n;
+			FLEX_ALLOC_STR(n, name, iter->refname);
+			hashcpy(n->sha1, iter->oid->hash);
+			n->next = refs_to_prune;
+			refs_to_prune = n;
+		}
+	}
+	if (ok != ITER_DONE)
+		die("error while iterating over references");
 
 	if (commit_packed_refs(refs))
 		die_errno("unable to overwrite old ref-pack file");
 
-	prune_refs(cbdata.ref_to_prune);
+	prune_refs(refs, refs_to_prune);
 	return 0;
 }
 
 /*
  * Rewrite the packed-refs file, omitting any refs listed in
  * 'refnames'. On error, leave packed-refs unchanged, write an error
