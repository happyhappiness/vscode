static int count_reflog_ent(struct object_id *ooid, struct object_id *noid,
		const char *email, timestamp_t timestamp, int tz,
		const char *message, void *cb_data)
{
	struct expire_reflog_policy_cb *cb = cb_data;
	if (!cb->cmd.expire_total || timestamp < cb->cmd.expire_total)
		cb->cmd.recno++;
	return 0;
}