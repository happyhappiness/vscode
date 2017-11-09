static void reflog_expiry_prepare(const char *refname,
				  const struct object_id *oid,
				  void *cb_data)
{
	struct expire_reflog_policy_cb *cb = cb_data;

	if (!cb->cmd.expire_unreachable || !strcmp(refname, "HEAD")) {
		cb->tip_commit = NULL;
		cb->unreachable_expire_kind = UE_HEAD;
	} else {
		cb->tip_commit = lookup_commit_reference_gently(oid, 1);
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