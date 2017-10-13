static int files_rename_ref(struct ref_store *ref_store,
			    const char *oldrefname, const char *newrefname,
			    const char *logmsg)
{
	struct files_ref_store *refs =
		files_downcast(ref_store, 0, "rename_ref");
	unsigned char sha1[20], orig_sha1[20];
	int flag = 0, logmoved = 0;
	struct ref_lock *lock;
	struct stat loginfo;
	int log = !lstat(git_path("logs/%s", oldrefname), &loginfo);
	struct strbuf err = STRBUF_INIT;

	if (log && S_ISLNK(loginfo.st_mode))
		return error("reflog for %s is a symlink", oldrefname);

	if (!resolve_ref_unsafe(oldrefname, RESOLVE_REF_READING | RESOLVE_REF_NO_RECURSE,
				orig_sha1, &flag))
		return error("refname %s not found", oldrefname);

	if (flag & REF_ISSYMREF)
		return error("refname %s is a symbolic ref, renaming it is not supported",
			oldrefname);
	if (!rename_ref_available(oldrefname, newrefname))
		return 1;

	if (log && rename(git_path("logs/%s", oldrefname), git_path(TMP_RENAMED_LOG)))
		return error("unable to move logfile logs/%s to "TMP_RENAMED_LOG": %s",
			oldrefname, strerror(errno));

	if (delete_ref(oldrefname, orig_sha1, REF_NODEREF)) {
		error("unable to delete old %s", oldrefname);
		goto rollback;
	}

	/*
	 * Since we are doing a shallow lookup, sha1 is not the
	 * correct value to pass to delete_ref as old_sha1. But that
	 * doesn't matter, because an old_sha1 check wouldn't add to
	 * the safety anyway; we want to delete the reference whatever
	 * its current value.
	 */
	if (!read_ref_full(newrefname, RESOLVE_REF_READING | RESOLVE_REF_NO_RECURSE,
			   sha1, NULL) &&
	    delete_ref(newrefname, NULL, REF_NODEREF)) {
		if (errno==EISDIR) {
			struct strbuf path = STRBUF_INIT;
			int result;

			strbuf_git_path(&path, "%s", newrefname);
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

	if (log && rename_tmp_log(newrefname))
		goto rollback;

	logmoved = log;

	lock = lock_ref_sha1_basic(refs, newrefname, NULL, NULL, NULL,
				   REF_NODEREF, NULL, &err);
	if (!lock) {
		error("unable to rename '%s' to '%s': %s", oldrefname, newrefname, err.buf);
		strbuf_release(&err);
		goto rollback;
	}
	hashcpy(lock->old_oid.hash, orig_sha1);

	if (write_ref_to_lockfile(lock, orig_sha1, &err) ||
	    commit_ref_update(refs, lock, orig_sha1, logmsg, &err)) {
		error("unable to write current sha1 into %s: %s", newrefname, err.buf);
		strbuf_release(&err);
		goto rollback;
	}

	return 0;

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
	if (write_ref_to_lockfile(lock, orig_sha1, &err) ||
	    commit_ref_update(refs, lock, orig_sha1, NULL, &err)) {
		error("unable to write current sha1 into %s: %s", oldrefname, err.buf);
		strbuf_release(&err);
	}
	log_all_ref_updates = flag;

 rollbacklog:
	if (logmoved && rename(git_path("logs/%s", newrefname), git_path("logs/%s", oldrefname)))
		error("unable to restore logfile %s from %s: %s",
			oldrefname, newrefname, strerror(errno));
	if (!logmoved && log &&
	    rename(git_path(TMP_RENAMED_LOG), git_path("logs/%s", oldrefname)))
		error("unable to restore logfile %s from "TMP_RENAMED_LOG": %s",
			oldrefname, strerror(errno));

	return 1;
}