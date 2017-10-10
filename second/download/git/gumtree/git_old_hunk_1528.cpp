	void *policy_cb;
	FILE *newlog;
	struct object_id last_kept_oid;
};

static int expire_reflog_ent(struct object_id *ooid, struct object_id *noid,
			     const char *email, unsigned long timestamp, int tz,
			     const char *message, void *cb_data)
{
	struct expire_reflog_cb *cb = cb_data;
	struct expire_reflog_policy_cb *policy_cb = cb->policy_cb;

	if (cb->flags & EXPIRE_REFLOGS_REWRITE)
		ooid = &cb->last_kept_oid;

	if ((*cb->should_prune_fn)(ooid->hash, noid->hash, email, timestamp, tz,
				   message, policy_cb)) {
		if (!cb->newlog)
			printf("would prune %s", message);
		else if (cb->flags & EXPIRE_REFLOGS_VERBOSE)
			printf("prune %s", message);
	} else {
		if (cb->newlog) {
			fprintf(cb->newlog, "%s %s %s %lu %+05d\t%s",
				oid_to_hex(ooid), oid_to_hex(noid),
				email, timestamp, tz, message);
			oidcpy(&cb->last_kept_oid, noid);
		}
		if (cb->flags & EXPIRE_REFLOGS_VERBOSE)
			printf("keep %s", message);
