static int files_rename_ref(struct ref_store *ref_store,
			    const char *oldrefname, const char *newrefname,
			    const char *logmsg)
{
	struct files_ref_store *refs =
		files_downcast(ref_store, REF_STORE_WRITE, "rename_ref");
	struct object_id oid, orig_oid;
	int flag = 0, logmoved = 0;
	struct ref_lock *lock;
	struct stat loginfo;
	struct strbuf sb_oldref = STRBUF_INIT;
	struct strbuf sb_newref = STRBUF_INIT;
	struct strbuf tmp_renamed_log = STRBUF_INIT;
	int log, ret;
	struct strbuf err = STRBUF_INIT;

	files_reflog_path(refs, &sb_oldref, oldrefname);
	files_reflog_path(refs, &sb_newref, newrefname);
	files_reflog_path(refs, &tmp_renamed_log, TMP_RENAMED_LOG);

	log = !lstat(sb_oldref.buf, &loginfo);
	if (log && S_ISLNK(loginfo.st_mode)) {
		ret = error("reflog for %s is a symlink", oldrefname);
		goto out;
	}

	if (!refs_resolve_ref_unsafe(&refs->base, oldrefname,
				     RESOLVE_REF_READING | RESOLVE_REF_NO_RECURSE,
				orig_oid.hash, &flag)) {
		ret = error("refname %s not found", oldrefname);
		goto out;
	}

	if (flag & REF_ISSYMREF) {
		ret = error("refname %s is a symbolic ref, renaming it is not supported",
			    oldrefname);
		goto out;
	}
	if (!refs_rename_ref_available(&refs->base, oldrefname, newrefname)) {
		ret = 1;
		goto out;
	}

	if (log && rename(sb_oldref.buf, tmp_renamed_log.buf)) {
		ret = error("unable to move logfile logs/%s to logs/"TMP_RENAMED_LOG": %s",
			    oldrefname, strerror(errno));
		goto out;
	}

	if (refs_delete_ref(&refs->base, logmsg, oldrefname,
			    orig_oid.hash, REF_NODEREF)) {
		error("unable to delete old %s", oldrefname);
		goto rollback;
	}

	/*
	 * Since we are doing a shallow lookup, oid is not the
	 * correct value to pass to delete_ref as old_oid. But that
	 * doesn't matter, because an old_oid check wouldn't add to
	 * the safety anyway; we want to delete the reference whatever
	 * its current value.
	 */
	if (!refs_read_ref_full(&refs->base, newrefname,
				RESOLVE_REF_READING | RESOLVE_REF_NO_RECURSE,
				oid.hash, NULL) &&
	    refs_delete_ref(&refs->base, NULL, newrefname,
			    NULL, REF_NODEREF)) {
		if (errno == EISDIR) {
			struct strbuf path = STRBUF_INIT;
			int result;

			files_ref_path(refs, &path, newrefname);
			result = remove_empty_directories(&path);
			strbuf_release(&path);

			if (result) {
				error("Directory not empty: %s", newrefname);
				goto rollback;
			}
		} else {
			error("unable to delete existing %s", newrefname);
			goto rollback;
		}
	}

	if (log && rename_tmp_log(refs, newrefname))
		goto rollback;

	logmoved = log;

	lock = lock_ref_sha1_basic(refs, newrefname, NULL, NULL, NULL,
				   REF_NODEREF, NULL, &err);
	if (!lock) {
		error("unable to rename '%s' to '%s': %s", oldrefname, newrefname, err.buf);
		strbuf_release(&err);
		goto rollback;
	}
	oidcpy(&lock->old_oid, &orig_oid);

	if (write_ref_to_lockfile(lock, &orig_oid, &err) ||
	    commit_ref_update(refs, lock, &orig_oid, logmsg, &err)) {
		error("unable to write current sha1 into %s: %s", newrefname, err.buf);
		strbuf_release(&err);
		goto rollback;
	}

	ret = 0;
	goto out;

 rollback:
	lock = lock_ref_sha1_basic(refs, oldrefname, NULL, NULL, NULL,
				   REF_NODEREF, NULL, &err);
	if (!lock) {
		error("unable to lock %s for rollback: %s", oldrefname, err.buf);
		strbuf_release(&err);
		goto rollbacklog;
	}

	flag = log_all_ref_updates;
	log_all_ref_updates = LOG_REFS_NONE;
	if (write_ref_to_lockfile(lock, &orig_oid, &err) ||
	    commit_ref_update(refs, lock, &orig_oid, NULL, &err)) {
		error("unable to write current sha1 into %s: %s", oldrefname, err.buf);
		strbuf_release(&err);
	}
	log_all_ref_updates = flag;

 rollbacklog:
	if (logmoved && rename(sb_newref.buf, sb_oldref.buf))
		error("unable to restore logfile %s from %s: %s",
			oldrefname, newrefname, strerror(errno));
	if (!logmoved && log &&
	    rename(tmp_renamed_log.buf, sb_oldref.buf))
		error("unable to restore logfile %s from logs/"TMP_RENAMED_LOG": %s",
			oldrefname, strerror(errno));
	ret = 1;
 out:
	strbuf_release(&sb_newref);
	strbuf_release(&sb_oldref);
	strbuf_release(&tmp_renamed_log);

	return ret;
}