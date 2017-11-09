static int should_expire_reflog_ent(struct object_id *ooid, struct object_id *noid,
				    const char *email, timestamp_t timestamp, int tz,
				    const char *message, void *cb_data)
{
	struct expire_reflog_policy_cb *cb = cb_data;
	struct commit *old, *new;

	if (timestamp < cb->cmd.expire_total)
		return 1;

	old = new = NULL;
	if (cb->cmd.stalefix &&
	    (!keep_entry(&old, ooid) || !keep_entry(&new, noid)))
		return 1;

	if (timestamp < cb->cmd.expire_unreachable) {
		if (cb->unreachable_expire_kind == UE_ALWAYS)
			return 1;
		if (unreachable(cb, old, ooid) || unreachable(cb, new, noid))
			return 1;
	}

	if (cb->cmd.recno && --(cb->cmd.recno) == 0)
		return 1;

	return 0;
}