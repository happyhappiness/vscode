static int count_reflog_ent(unsigned char *osha1, unsigned char *nsha1,
		const char *email, unsigned long timestamp, int tz,
		const char *message, void *cb_data)
{
	struct expire_reflog_policy_cb *cb = cb_data;
	if (!cb->cmd.expire_total || timestamp < cb->cmd.expire_total)
		cb->cmd.recno++;
	return 0;
}