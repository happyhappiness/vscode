static int read_ref_at_ent_oldest(struct object_id *ooid, struct object_id *noid,
				  const char *email, timestamp_t timestamp,
				  int tz, const char *message, void *cb_data)
{
	struct read_ref_at_cb *cb = cb_data;

	if (cb->msg)
		*cb->msg = xstrdup(message);
	if (cb->cutoff_time)
		*cb->cutoff_time = timestamp;
	if (cb->cutoff_tz)
		*cb->cutoff_tz = tz;
	if (cb->cutoff_cnt)
		*cb->cutoff_cnt = cb->reccnt;
	hashcpy(cb->sha1, ooid->hash);
	if (is_null_sha1(cb->sha1))
		hashcpy(cb->sha1, noid->hash);
	/* We just want the first entry */
	return 1;
}