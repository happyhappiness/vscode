 		}
 	}
 
 	errno = ELOOP;
 	return NULL;
 }
+
+/* backend functions */
+int refs_init_db(struct strbuf *err)
+{
+	struct ref_store *refs = get_ref_store(NULL);
+
+	return refs->be->init_db(refs, err);
+}
+
+const char *resolve_ref_unsafe(const char *refname, int resolve_flags,
+			       unsigned char *sha1, int *flags)
+{
+	return resolve_ref_recursively(get_ref_store(NULL), refname,
+				       resolve_flags, sha1, flags);
+}
+
+int resolve_gitlink_ref(const char *submodule, const char *refname,
+			unsigned char *sha1)
+{
+	size_t len = strlen(submodule);
+	struct ref_store *refs;
+	int flags;
+
+	while (len && submodule[len - 1] == '/')
+		len--;
+
+	if (!len)
+		return -1;
+
+	if (submodule[len]) {
+		/* We need to strip off one or more trailing slashes */
+		char *stripped = xmemdupz(submodule, len);
+
+		refs = get_ref_store(stripped);
+		free(stripped);
+	} else {
+		refs = get_ref_store(submodule);
+	}
+
+	if (!refs)
+		return -1;
+
+	if (!resolve_ref_recursively(refs, refname, 0, sha1, &flags) ||
+	    is_null_sha1(sha1))
+		return -1;
+	return 0;
+}
+
+/* A pointer to the ref_store for the main repository: */
+static struct ref_store *main_ref_store;
+
+/* A linked list of ref_stores for submodules: */
+static struct ref_store *submodule_ref_stores;
+
+void base_ref_store_init(struct ref_store *refs,
+			 const struct ref_storage_be *be,
+			 const char *submodule)
+{
+	refs->be = be;
+	if (!submodule) {
+		if (main_ref_store)
+			die("BUG: main_ref_store initialized twice");
+
+		refs->submodule = "";
+		refs->next = NULL;
+		main_ref_store = refs;
+	} else {
+		if (lookup_ref_store(submodule))
+			die("BUG: ref_store for submodule '%s' initialized twice",
+			    submodule);
+
+		refs->submodule = xstrdup(submodule);
+		refs->next = submodule_ref_stores;
+		submodule_ref_stores = refs;
+	}
+}
+
+struct ref_store *ref_store_init(const char *submodule)
+{
+	const char *be_name = "files";
+	struct ref_storage_be *be = find_ref_storage_backend(be_name);
+
+	if (!be)
+		die("BUG: reference backend %s is unknown", be_name);
+
+	if (!submodule || !*submodule)
+		return be->init(NULL);
+	else
+		return be->init(submodule);
+}
+
+struct ref_store *lookup_ref_store(const char *submodule)
+{
+	struct ref_store *refs;
+
+	if (!submodule || !*submodule)
+		return main_ref_store;
+
+	for (refs = submodule_ref_stores; refs; refs = refs->next) {
+		if (!strcmp(submodule, refs->submodule))
+			return refs;
+	}
+
+	return NULL;
+}
+
+struct ref_store *get_ref_store(const char *submodule)
+{
+	struct ref_store *refs;
+
+	if (!submodule || !*submodule) {
+		refs = lookup_ref_store(NULL);
+
+		if (!refs)
+			refs = ref_store_init(NULL);
+	} else {
+		refs = lookup_ref_store(submodule);
+
+		if (!refs) {
+			struct strbuf submodule_sb = STRBUF_INIT;
+
+			strbuf_addstr(&submodule_sb, submodule);
+			if (is_nonbare_repository_dir(&submodule_sb))
+				refs = ref_store_init(submodule);
+			strbuf_release(&submodule_sb);
+		}
+	}
+
+	return refs;
+}
+
+void assert_main_repository(struct ref_store *refs, const char *caller)
+{
+	if (*refs->submodule)
+		die("BUG: %s called for a submodule", caller);
+}
+
+/* backend functions */
+int pack_refs(unsigned int flags)
+{
+	struct ref_store *refs = get_ref_store(NULL);
+
+	return refs->be->pack_refs(refs, flags);
+}
+
+int peel_ref(const char *refname, unsigned char *sha1)
+{
+	struct ref_store *refs = get_ref_store(NULL);
+
+	return refs->be->peel_ref(refs, refname, sha1);
+}
+
+int create_symref(const char *ref_target, const char *refs_heads_master,
+		  const char *logmsg)
+{
+	struct ref_store *refs = get_ref_store(NULL);
+
+	return refs->be->create_symref(refs, ref_target, refs_heads_master,
+				       logmsg);
+}
+
+int ref_transaction_commit(struct ref_transaction *transaction,
+			   struct strbuf *err)
+{
+	struct ref_store *refs = get_ref_store(NULL);
+
+	return refs->be->transaction_commit(refs, transaction, err);
+}
+
+int verify_refname_available(const char *refname,
+			     const struct string_list *extra,
+			     const struct string_list *skip,
+			     struct strbuf *err)
+{
+	struct ref_store *refs = get_ref_store(NULL);
+
+	return refs->be->verify_refname_available(refs, refname, extra, skip, err);
+}
+
+int for_each_reflog(each_ref_fn fn, void *cb_data)
+{
+	struct ref_store *refs = get_ref_store(NULL);
+	struct ref_iterator *iter;
+
+	iter = refs->be->reflog_iterator_begin(refs);
+
+	return do_for_each_ref_iterator(iter, fn, cb_data);
+}
+
+int for_each_reflog_ent_reverse(const char *refname, each_reflog_ent_fn fn,
+				void *cb_data)
+{
+	struct ref_store *refs = get_ref_store(NULL);
+
+	return refs->be->for_each_reflog_ent_reverse(refs, refname,
+						     fn, cb_data);
+}
+
+int for_each_reflog_ent(const char *refname, each_reflog_ent_fn fn,
+			void *cb_data)
+{
+	struct ref_store *refs = get_ref_store(NULL);
+
+	return refs->be->for_each_reflog_ent(refs, refname, fn, cb_data);
+}
+
+int reflog_exists(const char *refname)
+{
+	struct ref_store *refs = get_ref_store(NULL);
+
+	return refs->be->reflog_exists(refs, refname);
+}
+
+int safe_create_reflog(const char *refname, int force_create,
+		       struct strbuf *err)
+{
+	struct ref_store *refs = get_ref_store(NULL);
+
+	return refs->be->create_reflog(refs, refname, force_create, err);
+}
+
+int delete_reflog(const char *refname)
+{
+	struct ref_store *refs = get_ref_store(NULL);
+
+	return refs->be->delete_reflog(refs, refname);
+}
+
+int reflog_expire(const char *refname, const unsigned char *sha1,
+		  unsigned int flags,
+		  reflog_expiry_prepare_fn prepare_fn,
+		  reflog_expiry_should_prune_fn should_prune_fn,
+		  reflog_expiry_cleanup_fn cleanup_fn,
+		  void *policy_cb_data)
+{
+	struct ref_store *refs = get_ref_store(NULL);
+
+	return refs->be->reflog_expire(refs, refname, sha1, flags,
+				       prepare_fn, should_prune_fn,
+				       cleanup_fn, policy_cb_data);
+}
+
+int initial_ref_transaction_commit(struct ref_transaction *transaction,
+				   struct strbuf *err)
+{
+	struct ref_store *refs = get_ref_store(NULL);
+
+	return refs->be->initial_transaction_commit(refs, transaction, err);
+}
+
+int delete_refs(struct string_list *refnames, unsigned int flags)
+{
+	struct ref_store *refs = get_ref_store(NULL);
+
+	return refs->be->delete_refs(refs, refnames, flags);
+}
+
+int rename_ref(const char *oldref, const char *newref, const char *logmsg)
+{
+	struct ref_store *refs = get_ref_store(NULL);
+
+	return refs->be->rename_ref(refs, oldref, newref, logmsg);
+}
