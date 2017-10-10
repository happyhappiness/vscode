 		return -1;
 
 	if (submodule[len]) {
 		/* We need to strip off one or more trailing slashes */
 		char *stripped = xmemdupz(submodule, len);
 
-		refs = get_ref_store(stripped);
+		refs = get_submodule_ref_store(stripped);
 		free(stripped);
 	} else {
-		refs = get_ref_store(submodule);
+		refs = get_submodule_ref_store(submodule);
 	}
 
 	if (!refs)
 		return -1;
 
-	if (!resolve_ref_recursively(refs, refname, 0, sha1, &flags) ||
+	if (!refs_resolve_ref_unsafe(refs, refname, 0, sha1, &flags) ||
 	    is_null_sha1(sha1))
 		return -1;
 	return 0;
 }
 
+struct submodule_hash_entry
+{
+	struct hashmap_entry ent; /* must be the first member! */
+
+	struct ref_store *refs;
+
+	/* NUL-terminated name of submodule: */
+	char submodule[FLEX_ARRAY];
+};
+
+static int submodule_hash_cmp(const void *entry, const void *entry_or_key,
+			      const void *keydata)
+{
+	const struct submodule_hash_entry *e1 = entry, *e2 = entry_or_key;
+	const char *submodule = keydata ? keydata : e2->submodule;
+
+	return strcmp(e1->submodule, submodule);
+}
+
+static struct submodule_hash_entry *alloc_submodule_hash_entry(
+		const char *submodule, struct ref_store *refs)
+{
+	struct submodule_hash_entry *entry;
+
+	FLEX_ALLOC_STR(entry, submodule, submodule);
+	hashmap_entry_init(entry, strhash(submodule));
+	entry->refs = refs;
+	return entry;
+}
+
 /* A pointer to the ref_store for the main repository: */
 static struct ref_store *main_ref_store;
 
-/* A linked list of ref_stores for submodules: */
-static struct ref_store *submodule_ref_stores;
+/* A hashmap of ref_stores, stored by submodule name: */
+static struct hashmap submodule_ref_stores;
 
-void base_ref_store_init(struct ref_store *refs,
-			 const struct ref_storage_be *be,
-			 const char *submodule)
+/*
+ * Return the ref_store instance for the specified submodule. If that
+ * ref_store hasn't been initialized yet, return NULL.
+ */
+static struct ref_store *lookup_submodule_ref_store(const char *submodule)
 {
-	refs->be = be;
-	if (!submodule) {
-		if (main_ref_store)
-			die("BUG: main_ref_store initialized twice");
-
-		refs->submodule = "";
-		refs->next = NULL;
-		main_ref_store = refs;
-	} else {
-		if (lookup_ref_store(submodule))
-			die("BUG: ref_store for submodule '%s' initialized twice",
-			    submodule);
+	struct submodule_hash_entry *entry;
 
-		refs->submodule = xstrdup(submodule);
-		refs->next = submodule_ref_stores;
-		submodule_ref_stores = refs;
-	}
+	if (!submodule_ref_stores.tablesize)
+		/* It's initialized on demand in register_ref_store(). */
+		return NULL;
+
+	entry = hashmap_get_from_hash(&submodule_ref_stores,
+				      strhash(submodule), submodule);
+	return entry ? entry->refs : NULL;
 }
 
-struct ref_store *ref_store_init(const char *submodule)
+/*
+ * Create, record, and return a ref_store instance for the specified
+ * gitdir.
+ */
+static struct ref_store *ref_store_init(const char *gitdir,
+					unsigned int flags)
 {
 	const char *be_name = "files";
 	struct ref_storage_be *be = find_ref_storage_backend(be_name);
+	struct ref_store *refs;
 
 	if (!be)
 		die("BUG: reference backend %s is unknown", be_name);
 
-	if (!submodule || !*submodule)
-		return be->init(NULL);
-	else
-		return be->init(submodule);
+	refs = be->init(gitdir, flags);
+	return refs;
 }
 
-struct ref_store *lookup_ref_store(const char *submodule)
+struct ref_store *get_main_ref_store(void)
 {
-	struct ref_store *refs;
-
-	if (!submodule || !*submodule)
+	if (main_ref_store)
 		return main_ref_store;
 
-	for (refs = submodule_ref_stores; refs; refs = refs->next) {
-		if (!strcmp(submodule, refs->submodule))
-			return refs;
-	}
+	main_ref_store = ref_store_init(get_git_dir(),
+					(REF_STORE_READ |
+					 REF_STORE_WRITE |
+					 REF_STORE_ODB |
+					 REF_STORE_MAIN));
+	return main_ref_store;
+}
 
-	return NULL;
+/*
+ * Register the specified ref_store to be the one that should be used
+ * for submodule. It is a fatal error to call this function twice for
+ * the same submodule.
+ */
+static void register_submodule_ref_store(struct ref_store *refs,
+					 const char *submodule)
+{
+	if (!submodule_ref_stores.tablesize)
+		hashmap_init(&submodule_ref_stores, submodule_hash_cmp, 0);
+
+	if (hashmap_put(&submodule_ref_stores,
+			alloc_submodule_hash_entry(submodule, refs)))
+		die("BUG: ref_store for submodule '%s' initialized twice",
+		    submodule);
 }
 
-struct ref_store *get_ref_store(const char *submodule)
+struct ref_store *get_submodule_ref_store(const char *submodule)
 {
+	struct strbuf submodule_sb = STRBUF_INIT;
 	struct ref_store *refs;
+	int ret;
 
 	if (!submodule || !*submodule) {
-		refs = lookup_ref_store(NULL);
+		/*
+		 * FIXME: This case is ideally not allowed. But that
+		 * can't happen until we clean up all the callers.
+		 */
+		return get_main_ref_store();
+	}
 
-		if (!refs)
-			refs = ref_store_init(NULL);
-	} else {
-		refs = lookup_ref_store(submodule);
+	refs = lookup_submodule_ref_store(submodule);
+	if (refs)
+		return refs;
 
-		if (!refs) {
-			struct strbuf submodule_sb = STRBUF_INIT;
+	strbuf_addstr(&submodule_sb, submodule);
+	ret = is_nonbare_repository_dir(&submodule_sb);
+	strbuf_release(&submodule_sb);
+	if (!ret)
+		return NULL;
 
-			strbuf_addstr(&submodule_sb, submodule);
-			if (is_nonbare_repository_dir(&submodule_sb))
-				refs = ref_store_init(submodule);
-			strbuf_release(&submodule_sb);
-		}
+	ret = submodule_to_gitdir(&submodule_sb, submodule);
+	if (ret) {
+		strbuf_release(&submodule_sb);
+		return NULL;
 	}
 
+	/* assume that add_submodule_odb() has been called */
+	refs = ref_store_init(submodule_sb.buf,
+			      REF_STORE_READ | REF_STORE_ODB);
+	register_submodule_ref_store(refs, submodule);
+
+	strbuf_release(&submodule_sb);
 	return refs;
 }
 
-void assert_main_repository(struct ref_store *refs, const char *caller)
+void base_ref_store_init(struct ref_store *refs,
+			 const struct ref_storage_be *be)
 {
-	if (*refs->submodule)
-		die("BUG: %s called for a submodule", caller);
+	refs->be = be;
 }
 
 /* backend functions */
-int pack_refs(unsigned int flags)
+int refs_pack_refs(struct ref_store *refs, unsigned int flags)
 {
-	struct ref_store *refs = get_ref_store(NULL);
-
 	return refs->be->pack_refs(refs, flags);
 }
 
+int refs_peel_ref(struct ref_store *refs, const char *refname,
+		  unsigned char *sha1)
+{
+	return refs->be->peel_ref(refs, refname, sha1);
+}
+
 int peel_ref(const char *refname, unsigned char *sha1)
 {
-	struct ref_store *refs = get_ref_store(NULL);
+	return refs_peel_ref(get_main_ref_store(), refname, sha1);
+}
 
-	return refs->be->peel_ref(refs, refname, sha1);
+int refs_create_symref(struct ref_store *refs,
+		       const char *ref_target,
+		       const char *refs_heads_master,
+		       const char *logmsg)
+{
+	return refs->be->create_symref(refs, ref_target,
+				       refs_heads_master,
+				       logmsg);
 }
 
 int create_symref(const char *ref_target, const char *refs_heads_master,
 		  const char *logmsg)
 {
-	struct ref_store *refs = get_ref_store(NULL);
-
-	return refs->be->create_symref(refs, ref_target, refs_heads_master,
-				       logmsg);
+	return refs_create_symref(get_main_ref_store(), ref_target,
+				  refs_heads_master, logmsg);
 }
 
 int ref_transaction_commit(struct ref_transaction *transaction,
 			   struct strbuf *err)
 {
-	struct ref_store *refs = get_ref_store(NULL);
+	struct ref_store *refs = transaction->ref_store;
+
+	if (getenv(GIT_QUARANTINE_ENVIRONMENT)) {
+		strbuf_addstr(err,
+			      _("ref updates forbidden inside quarantine environment"));
+		return -1;
+	}
 
 	return refs->be->transaction_commit(refs, transaction, err);
 }
 
-int verify_refname_available(const char *refname,
-			     const struct string_list *extra,
-			     const struct string_list *skip,
-			     struct strbuf *err)
-{
-	struct ref_store *refs = get_ref_store(NULL);
+int refs_verify_refname_available(struct ref_store *refs,
+				  const char *refname,
+				  const struct string_list *extras,
+				  const struct string_list *skip,
+				  struct strbuf *err)
+{
+	const char *slash;
+	const char *extra_refname;
+	struct strbuf dirname = STRBUF_INIT;
+	struct strbuf referent = STRBUF_INIT;
+	struct object_id oid;
+	unsigned int type;
+	struct ref_iterator *iter;
+	int ok;
+	int ret = -1;
+
+	/*
+	 * For the sake of comments in this function, suppose that
+	 * refname is "refs/foo/bar".
+	 */
+
+	assert(err);
+
+	strbuf_grow(&dirname, strlen(refname) + 1);
+	for (slash = strchr(refname, '/'); slash; slash = strchr(slash + 1, '/')) {
+		/* Expand dirname to the new prefix, not including the trailing slash: */
+		strbuf_add(&dirname, refname + dirname.len, slash - refname - dirname.len);
+
+		/*
+		 * We are still at a leading dir of the refname (e.g.,
+		 * "refs/foo"; if there is a reference with that name,
+		 * it is a conflict, *unless* it is in skip.
+		 */
+		if (skip && string_list_has_string(skip, dirname.buf))
+			continue;
+
+		if (!refs_read_raw_ref(refs, dirname.buf, oid.hash, &referent, &type)) {
+			strbuf_addf(err, "'%s' exists; cannot create '%s'",
+				    dirname.buf, refname);
+			goto cleanup;
+		}
+
+		if (extras && string_list_has_string(extras, dirname.buf)) {
+			strbuf_addf(err, "cannot process '%s' and '%s' at the same time",
+				    refname, dirname.buf);
+			goto cleanup;
+		}
+	}
+
+	/*
+	 * We are at the leaf of our refname (e.g., "refs/foo/bar").
+	 * There is no point in searching for a reference with that
+	 * name, because a refname isn't considered to conflict with
+	 * itself. But we still need to check for references whose
+	 * names are in the "refs/foo/bar/" namespace, because they
+	 * *do* conflict.
+	 */
+	strbuf_addstr(&dirname, refname + dirname.len);
+	strbuf_addch(&dirname, '/');
+
+	iter = refs_ref_iterator_begin(refs, dirname.buf, 0,
+				       DO_FOR_EACH_INCLUDE_BROKEN);
+	while ((ok = ref_iterator_advance(iter)) == ITER_OK) {
+		if (skip &&
+		    string_list_has_string(skip, iter->refname))
+			continue;
+
+		strbuf_addf(err, "'%s' exists; cannot create '%s'",
+			    iter->refname, refname);
+		ref_iterator_abort(iter);
+		goto cleanup;
+	}
+
+	if (ok != ITER_DONE)
+		die("BUG: error while iterating over references");
+
+	extra_refname = find_descendant_ref(dirname.buf, extras, skip);
+	if (extra_refname)
+		strbuf_addf(err, "cannot process '%s' and '%s' at the same time",
+			    refname, extra_refname);
+	else
+		ret = 0;
 
-	return refs->be->verify_refname_available(refs, refname, extra, skip, err);
+cleanup:
+	strbuf_release(&referent);
+	strbuf_release(&dirname);
+	return ret;
 }
 
-int for_each_reflog(each_ref_fn fn, void *cb_data)
+int refs_for_each_reflog(struct ref_store *refs, each_ref_fn fn, void *cb_data)
 {
-	struct ref_store *refs = get_ref_store(NULL);
 	struct ref_iterator *iter;
 
 	iter = refs->be->reflog_iterator_begin(refs);
 
 	return do_for_each_ref_iterator(iter, fn, cb_data);
 }
 
-int for_each_reflog_ent_reverse(const char *refname, each_reflog_ent_fn fn,
-				void *cb_data)
+int for_each_reflog(each_ref_fn fn, void *cb_data)
 {
-	struct ref_store *refs = get_ref_store(NULL);
+	return refs_for_each_reflog(get_main_ref_store(), fn, cb_data);
+}
 
+int refs_for_each_reflog_ent_reverse(struct ref_store *refs,
+				     const char *refname,
+				     each_reflog_ent_fn fn,
+				     void *cb_data)
+{
 	return refs->be->for_each_reflog_ent_reverse(refs, refname,
 						     fn, cb_data);
 }
 
+int for_each_reflog_ent_reverse(const char *refname, each_reflog_ent_fn fn,
+				void *cb_data)
+{
+	return refs_for_each_reflog_ent_reverse(get_main_ref_store(),
+						refname, fn, cb_data);
+}
+
+int refs_for_each_reflog_ent(struct ref_store *refs, const char *refname,
+			     each_reflog_ent_fn fn, void *cb_data)
+{
+	return refs->be->for_each_reflog_ent(refs, refname, fn, cb_data);
+}
+
 int for_each_reflog_ent(const char *refname, each_reflog_ent_fn fn,
 			void *cb_data)
 {
-	struct ref_store *refs = get_ref_store(NULL);
+	return refs_for_each_reflog_ent(get_main_ref_store(), refname,
+					fn, cb_data);
+}
 
-	return refs->be->for_each_reflog_ent(refs, refname, fn, cb_data);
+int refs_reflog_exists(struct ref_store *refs, const char *refname)
+{
+	return refs->be->reflog_exists(refs, refname);
 }
 
 int reflog_exists(const char *refname)
 {
-	struct ref_store *refs = get_ref_store(NULL);
+	return refs_reflog_exists(get_main_ref_store(), refname);
+}
 
-	return refs->be->reflog_exists(refs, refname);
+int refs_create_reflog(struct ref_store *refs, const char *refname,
+		       int force_create, struct strbuf *err)
+{
+	return refs->be->create_reflog(refs, refname, force_create, err);
 }
 
 int safe_create_reflog(const char *refname, int force_create,
 		       struct strbuf *err)
 {
-	struct ref_store *refs = get_ref_store(NULL);
+	return refs_create_reflog(get_main_ref_store(), refname,
+				  force_create, err);
+}
 
-	return refs->be->create_reflog(refs, refname, force_create, err);
+int refs_delete_reflog(struct ref_store *refs, const char *refname)
+{
+	return refs->be->delete_reflog(refs, refname);
 }
 
 int delete_reflog(const char *refname)
 {
-	struct ref_store *refs = get_ref_store(NULL);
+	return refs_delete_reflog(get_main_ref_store(), refname);
+}
 
-	return refs->be->delete_reflog(refs, refname);
+int refs_reflog_expire(struct ref_store *refs,
+		       const char *refname, const unsigned char *sha1,
+		       unsigned int flags,
+		       reflog_expiry_prepare_fn prepare_fn,
+		       reflog_expiry_should_prune_fn should_prune_fn,
+		       reflog_expiry_cleanup_fn cleanup_fn,
+		       void *policy_cb_data)
+{
+	return refs->be->reflog_expire(refs, refname, sha1, flags,
+				       prepare_fn, should_prune_fn,
+				       cleanup_fn, policy_cb_data);
 }
 
 int reflog_expire(const char *refname, const unsigned char *sha1,
 		  unsigned int flags,
 		  reflog_expiry_prepare_fn prepare_fn,
 		  reflog_expiry_should_prune_fn should_prune_fn,
 		  reflog_expiry_cleanup_fn cleanup_fn,
 		  void *policy_cb_data)
 {
-	struct ref_store *refs = get_ref_store(NULL);
-
-	return refs->be->reflog_expire(refs, refname, sha1, flags,
-				       prepare_fn, should_prune_fn,
-				       cleanup_fn, policy_cb_data);
+	return refs_reflog_expire(get_main_ref_store(),
+				  refname, sha1, flags,
+				  prepare_fn, should_prune_fn,
+				  cleanup_fn, policy_cb_data);
 }
 
 int initial_ref_transaction_commit(struct ref_transaction *transaction,
 				   struct strbuf *err)
 {
-	struct ref_store *refs = get_ref_store(NULL);
+	struct ref_store *refs = transaction->ref_store;
 
 	return refs->be->initial_transaction_commit(refs, transaction, err);
 }
 
-int delete_refs(struct string_list *refnames, unsigned int flags)
+int refs_delete_refs(struct ref_store *refs, struct string_list *refnames,
+		     unsigned int flags)
 {
-	struct ref_store *refs = get_ref_store(NULL);
-
 	return refs->be->delete_refs(refs, refnames, flags);
 }
 
-int rename_ref(const char *oldref, const char *newref, const char *logmsg)
+int delete_refs(struct string_list *refnames, unsigned int flags)
 {
-	struct ref_store *refs = get_ref_store(NULL);
+	return refs_delete_refs(get_main_ref_store(), refnames, flags);
+}
 
+int refs_rename_ref(struct ref_store *refs, const char *oldref,
+		    const char *newref, const char *logmsg)
+{
 	return refs->be->rename_ref(refs, oldref, newref, logmsg);
 }
+
+int rename_ref(const char *oldref, const char *newref, const char *logmsg)
+{
+	return refs_rename_ref(get_main_ref_store(), oldref, newref, logmsg);
+}
