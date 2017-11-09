static int fsck_handle_reflog_ent(struct object_id *ooid, struct object_id *noid,
		const char *email, timestamp_t timestamp, int tz,
		const char *message, void *cb_data)
{
	const char *refname = cb_data;

	if (verbose)
		fprintf(stderr, "Checking reflog %s->%s\n",
			oid_to_hex(ooid), oid_to_hex(noid));

	fsck_handle_reflog_oid(refname, ooid, 0);
	fsck_handle_reflog_oid(refname, noid, timestamp);
	return 0;
}