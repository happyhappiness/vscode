 	while (!ret && !strbuf_getwholeline(&sb, logfp, '\n'))
 		ret = show_one_reflog_ent(&sb, fn, cb_data);
 	fclose(logfp);
 	strbuf_release(&sb);
 	return ret;
 }
-/*
- * Call fn for each reflog in the namespace indicated by name.  name
- * must be empty or end with '/'.  Name will be used as a scratch
- * space, but its contents will be restored before return.
- */
-static int do_for_each_reflog(struct strbuf *name, each_ref_fn fn, void *cb_data)
-{
-	DIR *d = opendir(git_path("logs/%s", name->buf));
-	int retval = 0;
-	struct dirent *de;
-	int oldlen = name->len;
 
-	if (!d)
-		return name->len ? errno : 0;
+struct files_reflog_iterator {
+	struct ref_iterator base;
 
-	while ((de = readdir(d)) != NULL) {
-		struct stat st;
+	struct dir_iterator *dir_iterator;
+	struct object_id oid;
+};
 
-		if (de->d_name[0] == '.')
+static int files_reflog_iterator_advance(struct ref_iterator *ref_iterator)
+{
+	struct files_reflog_iterator *iter =
+		(struct files_reflog_iterator *)ref_iterator;
+	struct dir_iterator *diter = iter->dir_iterator;
+	int ok;
+
+	while ((ok = dir_iterator_advance(diter)) == ITER_OK) {
+		int flags;
+
+		if (!S_ISREG(diter->st.st_mode))
 			continue;
-		if (ends_with(de->d_name, ".lock"))
+		if (diter->basename[0] == '.')
+			continue;
+		if (ends_with(diter->basename, ".lock"))
 			continue;
-		strbuf_addstr(name, de->d_name);
-		if (stat(git_path("logs/%s", name->buf), &st) < 0) {
-			; /* silently ignore */
-		} else {
-			if (S_ISDIR(st.st_mode)) {
-				strbuf_addch(name, '/');
-				retval = do_for_each_reflog(name, fn, cb_data);
-			} else {
-				struct object_id oid;
 
-				if (read_ref_full(name->buf, 0, oid.hash, NULL))
-					retval = error("bad ref for %s", name->buf);
-				else
-					retval = fn(name->buf, &oid, 0, cb_data);
-			}
-			if (retval)
-				break;
+		if (read_ref_full(diter->relative_path, 0,
+				  iter->oid.hash, &flags)) {
+			error("bad ref for %s", diter->path.buf);
+			continue;
 		}
-		strbuf_setlen(name, oldlen);
+
+		iter->base.refname = diter->relative_path;
+		iter->base.oid = &iter->oid;
+		iter->base.flags = flags;
+		return ITER_OK;
 	}
-	closedir(d);
-	return retval;
+
+	iter->dir_iterator = NULL;
+	if (ref_iterator_abort(ref_iterator) == ITER_ERROR)
+		ok = ITER_ERROR;
+	return ok;
+}
+
+static int files_reflog_iterator_peel(struct ref_iterator *ref_iterator,
+				   struct object_id *peeled)
+{
+	die("BUG: ref_iterator_peel() called for reflog_iterator");
+}
+
+static int files_reflog_iterator_abort(struct ref_iterator *ref_iterator)
+{
+	struct files_reflog_iterator *iter =
+		(struct files_reflog_iterator *)ref_iterator;
+	int ok = ITER_DONE;
+
+	if (iter->dir_iterator)
+		ok = dir_iterator_abort(iter->dir_iterator);
+
+	base_ref_iterator_free(ref_iterator);
+	return ok;
+}
+
+static struct ref_iterator_vtable files_reflog_iterator_vtable = {
+	files_reflog_iterator_advance,
+	files_reflog_iterator_peel,
+	files_reflog_iterator_abort
+};
+
+struct ref_iterator *files_reflog_iterator_begin(void)
+{
+	struct files_reflog_iterator *iter = xcalloc(1, sizeof(*iter));
+	struct ref_iterator *ref_iterator = &iter->base;
+
+	base_ref_iterator_init(ref_iterator, &files_reflog_iterator_vtable);
+	iter->dir_iterator = dir_iterator_begin(git_path("logs"));
+	return ref_iterator;
 }
 
 int for_each_reflog(each_ref_fn fn, void *cb_data)
 {
-	int retval;
-	struct strbuf name;
-	strbuf_init(&name, PATH_MAX);
-	retval = do_for_each_reflog(&name, fn, cb_data);
-	strbuf_release(&name);
-	return retval;
+	return do_for_each_ref_iterator(files_reflog_iterator_begin(),
+					fn, cb_data);
 }
 
 static int ref_update_reject_duplicates(struct string_list *refnames,
 					struct strbuf *err)
 {
 	int i, n = refnames->nr;
 
 	assert(err);
 
 	for (i = 1; i < n; i++)
 		if (!strcmp(refnames->items[i - 1].string, refnames->items[i].string)) {
 			strbuf_addf(err,
-				    "Multiple updates for ref '%s' not allowed.",
+				    "multiple updates for ref '%s' not allowed.",
 				    refnames->items[i].string);
 			return 1;
 		}
 	return 0;
 }
 
+/*
+ * If update is a direct update of head_ref (the reference pointed to
+ * by HEAD), then add an extra REF_LOG_ONLY update for HEAD.
+ */
+static int split_head_update(struct ref_update *update,
+			     struct ref_transaction *transaction,
+			     const char *head_ref,
+			     struct string_list *affected_refnames,
+			     struct strbuf *err)
+{
+	struct string_list_item *item;
+	struct ref_update *new_update;
+
+	if ((update->flags & REF_LOG_ONLY) ||
+	    (update->flags & REF_ISPRUNING) ||
+	    (update->flags & REF_UPDATE_VIA_HEAD))
+		return 0;
+
+	if (strcmp(update->refname, head_ref))
+		return 0;
+
+	/*
+	 * First make sure that HEAD is not already in the
+	 * transaction. This insertion is O(N) in the transaction
+	 * size, but it happens at most once per transaction.
+	 */
+	item = string_list_insert(affected_refnames, "HEAD");
+	if (item->util) {
+		/* An entry already existed */
+		strbuf_addf(err,
+			    "multiple updates for 'HEAD' (including one "
+			    "via its referent '%s') are not allowed",
+			    update->refname);
+		return TRANSACTION_NAME_CONFLICT;
+	}
+
+	new_update = ref_transaction_add_update(
+			transaction, "HEAD",
+			update->flags | REF_LOG_ONLY | REF_NODEREF,
+			update->new_sha1, update->old_sha1,
+			update->msg);
+
+	item->util = new_update;
+
+	return 0;
+}
+
+/*
+ * update is for a symref that points at referent and doesn't have
+ * REF_NODEREF set. Split it into two updates:
+ * - The original update, but with REF_LOG_ONLY and REF_NODEREF set
+ * - A new, separate update for the referent reference
+ * Note that the new update will itself be subject to splitting when
+ * the iteration gets to it.
+ */
+static int split_symref_update(struct ref_update *update,
+			       const char *referent,
+			       struct ref_transaction *transaction,
+			       struct string_list *affected_refnames,
+			       struct strbuf *err)
+{
+	struct string_list_item *item;
+	struct ref_update *new_update;
+	unsigned int new_flags;
+
+	/*
+	 * First make sure that referent is not already in the
+	 * transaction. This insertion is O(N) in the transaction
+	 * size, but it happens at most once per symref in a
+	 * transaction.
+	 */
+	item = string_list_insert(affected_refnames, referent);
+	if (item->util) {
+		/* An entry already existed */
+		strbuf_addf(err,
+			    "multiple updates for '%s' (including one "
+			    "via symref '%s') are not allowed",
+			    referent, update->refname);
+		return TRANSACTION_NAME_CONFLICT;
+	}
+
+	new_flags = update->flags;
+	if (!strcmp(update->refname, "HEAD")) {
+		/*
+		 * Record that the new update came via HEAD, so that
+		 * when we process it, split_head_update() doesn't try
+		 * to add another reflog update for HEAD. Note that
+		 * this bit will be propagated if the new_update
+		 * itself needs to be split.
+		 */
+		new_flags |= REF_UPDATE_VIA_HEAD;
+	}
+
+	new_update = ref_transaction_add_update(
+			transaction, referent, new_flags,
+			update->new_sha1, update->old_sha1,
+			update->msg);
+
+	new_update->parent_update = update;
+
+	/*
+	 * Change the symbolic ref update to log only. Also, it
+	 * doesn't need to check its old SHA-1 value, as that will be
+	 * done when new_update is processed.
+	 */
+	update->flags |= REF_LOG_ONLY | REF_NODEREF;
+	update->flags &= ~REF_HAVE_OLD;
+
+	item->util = new_update;
+
+	return 0;
+}
+
+/*
+ * Return the refname under which update was originally requested.
+ */
+static const char *original_update_refname(struct ref_update *update)
+{
+	while (update->parent_update)
+		update = update->parent_update;
+
+	return update->refname;
+}
+
+/*
+ * Check whether the REF_HAVE_OLD and old_oid values stored in update
+ * are consistent with oid, which is the reference's current value. If
+ * everything is OK, return 0; otherwise, write an error message to
+ * err and return -1.
+ */
+static int check_old_oid(struct ref_update *update, struct object_id *oid,
+			 struct strbuf *err)
+{
+	if (!(update->flags & REF_HAVE_OLD) ||
+		   !hashcmp(oid->hash, update->old_sha1))
+		return 0;
+
+	if (is_null_sha1(update->old_sha1))
+		strbuf_addf(err, "cannot lock ref '%s': "
+			    "reference already exists",
+			    original_update_refname(update));
+	else if (is_null_oid(oid))
+		strbuf_addf(err, "cannot lock ref '%s': "
+			    "reference is missing but expected %s",
+			    original_update_refname(update),
+			    sha1_to_hex(update->old_sha1));
+	else
+		strbuf_addf(err, "cannot lock ref '%s': "
+			    "is at %s but expected %s",
+			    original_update_refname(update),
+			    oid_to_hex(oid),
+			    sha1_to_hex(update->old_sha1));
+
+	return -1;
+}
+
+/*
+ * Prepare for carrying out update:
+ * - Lock the reference referred to by update.
+ * - Read the reference under lock.
+ * - Check that its old SHA-1 value (if specified) is correct, and in
+ *   any case record it in update->lock->old_oid for later use when
+ *   writing the reflog.
+ * - If it is a symref update without REF_NODEREF, split it up into a
+ *   REF_LOG_ONLY update of the symref and add a separate update for
+ *   the referent to transaction.
+ * - If it is an update of head_ref, add a corresponding REF_LOG_ONLY
+ *   update of HEAD.
+ */
+static int lock_ref_for_update(struct ref_update *update,
+			       struct ref_transaction *transaction,
+			       const char *head_ref,
+			       struct string_list *affected_refnames,
+			       struct strbuf *err)
+{
+	struct strbuf referent = STRBUF_INIT;
+	int mustexist = (update->flags & REF_HAVE_OLD) &&
+		!is_null_sha1(update->old_sha1);
+	int ret;
+	struct ref_lock *lock;
+
+	if ((update->flags & REF_HAVE_NEW) && is_null_sha1(update->new_sha1))
+		update->flags |= REF_DELETING;
+
+	if (head_ref) {
+		ret = split_head_update(update, transaction, head_ref,
+					affected_refnames, err);
+		if (ret)
+			return ret;
+	}
+
+	ret = lock_raw_ref(update->refname, mustexist,
+			   affected_refnames, NULL,
+			   &update->lock, &referent,
+			   &update->type, err);
+
+	if (ret) {
+		char *reason;
+
+		reason = strbuf_detach(err, NULL);
+		strbuf_addf(err, "cannot lock ref '%s': %s",
+			    original_update_refname(update), reason);
+		free(reason);
+		return ret;
+	}
+
+	lock = update->lock;
+
+	if (update->type & REF_ISSYMREF) {
+		if (update->flags & REF_NODEREF) {
+			/*
+			 * We won't be reading the referent as part of
+			 * the transaction, so we have to read it here
+			 * to record and possibly check old_sha1:
+			 */
+			if (read_ref_full(referent.buf, 0,
+					  lock->old_oid.hash, NULL)) {
+				if (update->flags & REF_HAVE_OLD) {
+					strbuf_addf(err, "cannot lock ref '%s': "
+						    "error reading reference",
+						    original_update_refname(update));
+					return -1;
+				}
+			} else if (check_old_oid(update, &lock->old_oid, err)) {
+				return TRANSACTION_GENERIC_ERROR;
+			}
+		} else {
+			/*
+			 * Create a new update for the reference this
+			 * symref is pointing at. Also, we will record
+			 * and verify old_sha1 for this update as part
+			 * of processing the split-off update, so we
+			 * don't have to do it here.
+			 */
+			ret = split_symref_update(update, referent.buf, transaction,
+						  affected_refnames, err);
+			if (ret)
+				return ret;
+		}
+	} else {
+		struct ref_update *parent_update;
+
+		if (check_old_oid(update, &lock->old_oid, err))
+			return TRANSACTION_GENERIC_ERROR;
+
+		/*
+		 * If this update is happening indirectly because of a
+		 * symref update, record the old SHA-1 in the parent
+		 * update:
+		 */
+		for (parent_update = update->parent_update;
+		     parent_update;
+		     parent_update = parent_update->parent_update) {
+			oidcpy(&parent_update->lock->old_oid, &lock->old_oid);
+		}
+	}
+
+	if ((update->flags & REF_HAVE_NEW) &&
+	    !(update->flags & REF_DELETING) &&
+	    !(update->flags & REF_LOG_ONLY)) {
+		if (!(update->type & REF_ISSYMREF) &&
+		    !hashcmp(lock->old_oid.hash, update->new_sha1)) {
+			/*
+			 * The reference already has the desired
+			 * value, so we don't need to write it.
+			 */
+		} else if (write_ref_to_lockfile(lock, update->new_sha1,
+						 err)) {
+			char *write_err = strbuf_detach(err, NULL);
+
+			/*
+			 * The lock was freed upon failure of
+			 * write_ref_to_lockfile():
+			 */
+			update->lock = NULL;
+			strbuf_addf(err,
+				    "cannot update ref '%s': %s",
+				    update->refname, write_err);
+			free(write_err);
+			return TRANSACTION_GENERIC_ERROR;
+		} else {
+			update->flags |= REF_NEEDS_COMMIT;
+		}
+	}
+	if (!(update->flags & REF_NEEDS_COMMIT)) {
+		/*
+		 * We didn't call write_ref_to_lockfile(), so
+		 * the lockfile is still open. Close it to
+		 * free up the file descriptor:
+		 */
+		if (close_ref(lock)) {
+			strbuf_addf(err, "couldn't close '%s.lock'",
+				    update->refname);
+			return TRANSACTION_GENERIC_ERROR;
+		}
+	}
+	return 0;
+}
+
 int ref_transaction_commit(struct ref_transaction *transaction,
 			   struct strbuf *err)
 {
 	int ret = 0, i;
-	int n = transaction->nr;
-	struct ref_update **updates = transaction->updates;
 	struct string_list refs_to_delete = STRING_LIST_INIT_NODUP;
 	struct string_list_item *ref_to_delete;
 	struct string_list affected_refnames = STRING_LIST_INIT_NODUP;
+	char *head_ref = NULL;
+	int head_type;
+	struct object_id head_oid;
 
 	assert(err);
 
 	if (transaction->state != REF_TRANSACTION_OPEN)
 		die("BUG: commit called for transaction that is not open");
 
-	if (!n) {
+	if (!transaction->nr) {
 		transaction->state = REF_TRANSACTION_CLOSED;
 		return 0;
 	}
 
-	/* Fail if a refname appears more than once in the transaction: */
-	for (i = 0; i < n; i++)
-		string_list_append(&affected_refnames, updates[i]->refname);
+	/*
+	 * Fail if a refname appears more than once in the
+	 * transaction. (If we end up splitting up any updates using
+	 * split_symref_update() or split_head_update(), those
+	 * functions will check that the new updates don't have the
+	 * same refname as any existing ones.)
+	 */
+	for (i = 0; i < transaction->nr; i++) {
+		struct ref_update *update = transaction->updates[i];
+		struct string_list_item *item =
+			string_list_append(&affected_refnames, update->refname);
+
+		/*
+		 * We store a pointer to update in item->util, but at
+		 * the moment we never use the value of this field
+		 * except to check whether it is non-NULL.
+		 */
+		item->util = update;
+	}
 	string_list_sort(&affected_refnames);
 	if (ref_update_reject_duplicates(&affected_refnames, err)) {
 		ret = TRANSACTION_GENERIC_ERROR;
 		goto cleanup;
 	}
 
 	/*
+	 * Special hack: If a branch is updated directly and HEAD
+	 * points to it (may happen on the remote side of a push
+	 * for example) then logically the HEAD reflog should be
+	 * updated too.
+	 *
+	 * A generic solution would require reverse symref lookups,
+	 * but finding all symrefs pointing to a given branch would be
+	 * rather costly for this rare event (the direct update of a
+	 * branch) to be worth it. So let's cheat and check with HEAD
+	 * only, which should cover 99% of all usage scenarios (even
+	 * 100% of the default ones).
+	 *
+	 * So if HEAD is a symbolic reference, then record the name of
+	 * the reference that it points to. If we see an update of
+	 * head_ref within the transaction, then split_head_update()
+	 * arranges for the reflog of HEAD to be updated, too.
+	 */
+	head_ref = resolve_refdup("HEAD", RESOLVE_REF_NO_RECURSE,
+				  head_oid.hash, &head_type);
+
+	if (head_ref && !(head_type & REF_ISSYMREF)) {
+		free(head_ref);
+		head_ref = NULL;
+	}
+
+	/*
 	 * Acquire all locks, verify old values if provided, check
 	 * that new values are valid, and write new values to the
 	 * lockfiles, ready to be activated. Only keep one lockfile
 	 * open at a time to avoid running out of file descriptors.
 	 */
-	for (i = 0; i < n; i++) {
-		struct ref_update *update = updates[i];
+	for (i = 0; i < transaction->nr; i++) {
+		struct ref_update *update = transaction->updates[i];
 
-		if ((update->flags & REF_HAVE_NEW) &&
-		    is_null_sha1(update->new_sha1))
-			update->flags |= REF_DELETING;
-		update->lock = lock_ref_sha1_basic(
-				update->refname,
-				((update->flags & REF_HAVE_OLD) ?
-				 update->old_sha1 : NULL),
-				&affected_refnames, NULL,
-				update->flags,
-				&update->type,
-				err);
-		if (!update->lock) {
-			char *reason;
-
-			ret = (errno == ENOTDIR)
-				? TRANSACTION_NAME_CONFLICT
-				: TRANSACTION_GENERIC_ERROR;
-			reason = strbuf_detach(err, NULL);
-			strbuf_addf(err, "cannot lock ref '%s': %s",
-				    update->refname, reason);
-			free(reason);
+		ret = lock_ref_for_update(update, transaction, head_ref,
+					  &affected_refnames, err);
+		if (ret)
 			goto cleanup;
-		}
-		if ((update->flags & REF_HAVE_NEW) &&
-		    !(update->flags & REF_DELETING)) {
-			int overwriting_symref = ((update->type & REF_ISSYMREF) &&
-						  (update->flags & REF_NODEREF));
-
-			if (!overwriting_symref &&
-			    !hashcmp(update->lock->old_oid.hash, update->new_sha1)) {
-				/*
-				 * The reference already has the desired
-				 * value, so we don't need to write it.
-				 */
-			} else if (write_ref_to_lockfile(update->lock,
-							 update->new_sha1,
-							 err)) {
-				char *write_err = strbuf_detach(err, NULL);
+	}
 
-				/*
-				 * The lock was freed upon failure of
-				 * write_ref_to_lockfile():
-				 */
+	/* Perform updates first so live commits remain referenced */
+	for (i = 0; i < transaction->nr; i++) {
+		struct ref_update *update = transaction->updates[i];
+		struct ref_lock *lock = update->lock;
+
+		if (update->flags & REF_NEEDS_COMMIT ||
+		    update->flags & REF_LOG_ONLY) {
+			if (log_ref_write(lock->ref_name, lock->old_oid.hash,
+					  update->new_sha1,
+					  update->msg, update->flags, err)) {
+				char *old_msg = strbuf_detach(err, NULL);
+
+				strbuf_addf(err, "cannot update the ref '%s': %s",
+					    lock->ref_name, old_msg);
+				free(old_msg);
+				unlock_ref(lock);
 				update->lock = NULL;
-				strbuf_addf(err,
-					    "cannot update the ref '%s': %s",
-					    update->refname, write_err);
-				free(write_err);
 				ret = TRANSACTION_GENERIC_ERROR;
 				goto cleanup;
-			} else {
-				update->flags |= REF_NEEDS_COMMIT;
 			}
 		}
-		if (!(update->flags & REF_NEEDS_COMMIT)) {
-			/*
-			 * We didn't have to write anything to the lockfile.
-			 * Close it to free up the file descriptor:
-			 */
-			if (close_ref(update->lock)) {
-				strbuf_addf(err, "Couldn't close %s.lock",
-					    update->refname);
-				goto cleanup;
-			}
-		}
-	}
-
-	/* Perform updates first so live commits remain referenced */
-	for (i = 0; i < n; i++) {
-		struct ref_update *update = updates[i];
-
 		if (update->flags & REF_NEEDS_COMMIT) {
-			if (commit_ref_update(update->lock,
-					      update->new_sha1, update->msg,
-					      update->flags, err)) {
-				/* freed by commit_ref_update(): */
+			clear_loose_ref_cache(&ref_cache);
+			if (commit_ref(lock)) {
+				strbuf_addf(err, "couldn't set '%s'", lock->ref_name);
+				unlock_ref(lock);
 				update->lock = NULL;
 				ret = TRANSACTION_GENERIC_ERROR;
 				goto cleanup;
-			} else {
-				/* freed by commit_ref_update(): */
-				update->lock = NULL;
 			}
 		}
 	}
-
 	/* Perform deletes now that updates are safely completed */
-	for (i = 0; i < n; i++) {
-		struct ref_update *update = updates[i];
+	for (i = 0; i < transaction->nr; i++) {
+		struct ref_update *update = transaction->updates[i];
 
-		if (update->flags & REF_DELETING) {
+		if (update->flags & REF_DELETING &&
+		    !(update->flags & REF_LOG_ONLY)) {
 			if (delete_ref_loose(update->lock, update->type, err)) {
 				ret = TRANSACTION_GENERIC_ERROR;
 				goto cleanup;
 			}
 
 			if (!(update->flags & REF_ISPRUNING))
