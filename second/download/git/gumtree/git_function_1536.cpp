static int expire_reflog(const char *ref, const unsigned char *sha1, int unused, void *cb_data)
{
	struct cmd_reflog_expire_cb *cmd = cb_data;
	struct expire_reflog_cb cb;
	struct ref_lock *lock;
	char *log_file, *newlog_path = NULL;
	struct commit *tip_commit;
	struct commit_list *tips;
	int status = 0;

	memset(&cb, 0, sizeof(cb));

	/*
	 * we take the lock for the ref itself to prevent it from
	 * getting updated.
	 */
	lock = lock_any_ref_for_update(ref, sha1, 0, NULL);
	if (!lock)
		return error("cannot lock ref '%s'", ref);
	log_file = git_pathdup("logs/%s", ref);
	if (!reflog_exists(ref))
		goto finish;
	if (!cmd->dry_run) {
		newlog_path = git_pathdup("logs/%s.lock", ref);
		cb.newlog = fopen(newlog_path, "w");
	}

	cb.cmd = cmd;

	if (!cmd->expire_unreachable || !strcmp(ref, "HEAD")) {
		tip_commit = NULL;
		cb.unreachable_expire_kind = UE_HEAD;
	} else {
		tip_commit = lookup_commit_reference_gently(sha1, 1);
		if (!tip_commit)
			cb.unreachable_expire_kind = UE_ALWAYS;
		else
			cb.unreachable_expire_kind = UE_NORMAL;
	}

	if (cmd->expire_unreachable <= cmd->expire_total)
		cb.unreachable_expire_kind = UE_ALWAYS;

	cb.mark_list = NULL;
	tips = NULL;
	if (cb.unreachable_expire_kind != UE_ALWAYS) {
		if (cb.unreachable_expire_kind == UE_HEAD) {
			struct commit_list *elem;
			for_each_ref(push_tip_to_list, &tips);
			for (elem = tips; elem; elem = elem->next)
				commit_list_insert(elem->item, &cb.mark_list);
		} else {
			commit_list_insert(tip_commit, &cb.mark_list);
		}
		cb.mark_limit = cmd->expire_total;
		mark_reachable(&cb);
	}

	for_each_reflog_ent(ref, expire_reflog_ent, &cb);

	if (cb.unreachable_expire_kind != UE_ALWAYS) {
		if (cb.unreachable_expire_kind == UE_HEAD) {
			struct commit_list *elem;
			for (elem = tips; elem; elem = elem->next)
				clear_commit_marks(elem->item, REACHABLE);
			free_commit_list(tips);
		} else {
			clear_commit_marks(tip_commit, REACHABLE);
		}
	}
 finish:
	if (cb.newlog) {
		if (fclose(cb.newlog)) {
			status |= error("%s: %s", strerror(errno),
					newlog_path);
			unlink(newlog_path);
		} else if (cmd->updateref &&
			(write_in_full(lock->lock_fd,
				sha1_to_hex(cb.last_kept_sha1), 40) != 40 ||
			 write_str_in_full(lock->lock_fd, "\n") != 1 ||
			 close_ref(lock) < 0)) {
			status |= error("Couldn't write %s",
				lock->lk->filename);
			unlink(newlog_path);
		} else if (rename(newlog_path, log_file)) {
			status |= error("cannot rename %s to %s",
					newlog_path, log_file);
			unlink(newlog_path);
		} else if (cmd->updateref && commit_ref(lock)) {
			status |= error("Couldn't set %s", lock->ref_name);
		} else {
			adjust_shared_perm(log_file);
		}
	}
	free(newlog_path);
	free(log_file);
	unlock_ref(lock);
	return status;
}