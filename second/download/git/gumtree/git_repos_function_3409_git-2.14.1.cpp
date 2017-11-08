static int read_ref_at_ent(struct object_id *ooid, struct object_id *noid,
		const char *email, timestamp_t timestamp, int tz,
		const char *message, void *cb_data)
{
	struct read_ref_at_cb *cb = cb_data;

	cb->reccnt++;
	cb->tz = tz;
	cb->date = timestamp;

	if (timestamp <= cb->at_time || cb->cnt == 0) {
		if (cb->msg)
			*cb->msg = xstrdup(message);
		if (cb->cutoff_time)
			*cb->cutoff_time = timestamp;
		if (cb->cutoff_tz)
			*cb->cutoff_tz = tz;
		if (cb->cutoff_cnt)
			*cb->cutoff_cnt = cb->reccnt - 1;
		/*
		 * we have not yet updated cb->[n|o]sha1 so they still
		 * hold the values for the previous record.
		 */
		if (!is_null_sha1(cb->osha1)) {
			hashcpy(cb->sha1, noid->hash);
			if (hashcmp(cb->osha1, noid->hash))
				warning("Log for ref %s has gap after %s.",
					cb->refname, show_date(cb->date, cb->tz, DATE_MODE(RFC2822)));
		}
		else if (cb->date == cb->at_time)
			hashcpy(cb->sha1, noid->hash);
		else if (hashcmp(noid->hash, cb->sha1))
			warning("Log for ref %s unexpectedly ended on %s.",
				cb->refname, show_date(cb->date, cb->tz,
						       DATE_MODE(RFC2822)));
		hashcpy(cb->osha1, ooid->hash);
		hashcpy(cb->nsha1, noid->hash);
		cb->found_it = 1;
		return 1;
	}
	hashcpy(cb->osha1, ooid->hash);
	hashcpy(cb->nsha1, noid->hash);
	if (cb->cnt > 0)
		cb->cnt--;
	return 0;
}