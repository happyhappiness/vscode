		mark_reachable(cb);
	}

	return !(commit->object.flags & REACHABLE);
}

/*
 * Return true iff the specified reflog entry should be expired.
 */
static int should_expire_reflog_ent(unsigned char *osha1, unsigned char *nsha1,
				    const char *email, unsigned long timestamp, int tz,
				    const char *message, void *cb_data)
{
	struct expire_reflog_policy_cb *cb = cb_data;
	struct commit *old, *new;

	if (timestamp < cb->cmd.expire_total)
		return 1;

	old = new = NULL;
	if (cb->cmd.stalefix &&
	    (!keep_entry(&old, osha1) || !keep_entry(&new, nsha1)))
		return 1;

	if (timestamp < cb->cmd.expire_unreachable) {
		if (cb->unreachable_expire_kind == UE_ALWAYS)
			return 1;
		if (unreachable(cb, old, osha1) || unreachable(cb, new, nsha1))
			return 1;
	}

	if (cb->cmd.recno && --(cb->cmd.recno) == 0)
		return 1;

	return 0;
}

static int push_tip_to_list(const char *refname, const unsigned char *sha1,
			    int flags, void *cb_data)
{
	struct commit_list **list = cb_data;
	struct commit *tip_commit;
	if (flags & REF_ISSYMREF)
		return 0;
	tip_commit = lookup_commit_reference_gently(sha1, 1);
	if (!tip_commit)
		return 0;
	commit_list_insert(tip_commit, list);
	return 0;
}

static void reflog_expiry_prepare(const char *refname,
				  const unsigned char *sha1,
				  void *cb_data)
{
	struct expire_reflog_policy_cb *cb = cb_data;

	if (!cb->cmd.expire_unreachable || !strcmp(refname, "HEAD")) {
		cb->tip_commit = NULL;
		cb->unreachable_expire_kind = UE_HEAD;
	} else {
		cb->tip_commit = lookup_commit_reference_gently(sha1, 1);
		if (!cb->tip_commit)
			cb->unreachable_expire_kind = UE_ALWAYS;
		else
			cb->unreachable_expire_kind = UE_NORMAL;
	}

	if (cb->cmd.expire_unreachable <= cb->cmd.expire_total)
		cb->unreachable_expire_kind = UE_ALWAYS;

	cb->mark_list = NULL;
	cb->tips = NULL;
	if (cb->unreachable_expire_kind != UE_ALWAYS) {
		if (cb->unreachable_expire_kind == UE_HEAD) {
			struct commit_list *elem;
			for_each_ref(push_tip_to_list, &cb->tips);
			for (elem = cb->tips; elem; elem = elem->next)
				commit_list_insert(elem->item, &cb->mark_list);
		} else {
			commit_list_insert(cb->tip_commit, &cb->mark_list);
		}
		cb->mark_limit = cb->cmd.expire_total;
		mark_reachable(cb);
	}
}

static void reflog_expiry_cleanup(void *cb_data)
{
	struct expire_reflog_policy_cb *cb = cb_data;

	if (cb->unreachable_expire_kind != UE_ALWAYS) {
		if (cb->unreachable_expire_kind == UE_HEAD) {
			struct commit_list *elem;
			for (elem = cb->tips; elem; elem = elem->next)
				clear_commit_marks(elem->item, REACHABLE);
			free_commit_list(cb->tips);
		} else {
			clear_commit_marks(cb->tip_commit, REACHABLE);
		}
	}
}

static int collect_reflog(const char *ref, const unsigned char *sha1, int unused, void *cb_data)
{
	struct collected_reflog *e;
	struct collect_reflog_cb *cb = cb_data;
