static int expire_reflog_ent(unsigned char *osha1, unsigned char *nsha1,
		const char *email, unsigned long timestamp, int tz,
		const char *message, void *cb_data)
{
	struct expire_reflog_cb *cb = cb_data;
	struct commit *old, *new;

	if (timestamp < cb->cmd->expire_total)
		goto prune;

	if (cb->cmd->rewrite)
		osha1 = cb->last_kept_sha1;

	old = new = NULL;
	if (cb->cmd->stalefix &&
	    (!keep_entry(&old, osha1) || !keep_entry(&new, nsha1)))
		goto prune;

	if (timestamp < cb->cmd->expire_unreachable) {
		if (cb->unreachable_expire_kind == UE_ALWAYS)
			goto prune;
		if (unreachable(cb, old, osha1) || unreachable(cb, new, nsha1))
			goto prune;
	}

	if (cb->cmd->recno && --(cb->cmd->recno) == 0)
		goto prune;

	if (cb->newlog) {
		char sign = (tz < 0) ? '-' : '+';
		int zone = (tz < 0) ? (-tz) : tz;
		fprintf(cb->newlog, "%s %s %s %lu %c%04d\t%s",
			sha1_to_hex(osha1), sha1_to_hex(nsha1),
			email, timestamp, sign, zone,
			message);
		hashcpy(cb->last_kept_sha1, nsha1);
	}
	if (cb->cmd->verbose)
		printf("keep %s", message);
	return 0;
 prune:
	if (!cb->newlog)
		printf("would prune %s", message);
	else if (cb->cmd->verbose)
		printf("prune %s", message);
	return 0;
}