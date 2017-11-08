static int handle_one_reflog_ent(struct object_id *ooid, struct object_id *noid,
		const char *email, timestamp_t timestamp, int tz,
		const char *message, void *cb_data)
{
	handle_one_reflog_commit(ooid, cb_data);
	handle_one_reflog_commit(noid, cb_data);
	return 0;
}