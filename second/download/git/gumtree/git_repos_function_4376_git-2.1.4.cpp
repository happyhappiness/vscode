static int count_reflog_ent(unsigned char *osha1, unsigned char *nsha1,
		const char *email, unsigned long timestamp, int tz,
		const char *message, void *cb_data)
{
	struct cmd_reflog_expire_cb *cb = cb_data;
	if (!cb->expire_total || timestamp < cb->expire_total)
		cb->recno++;
	return 0;
}