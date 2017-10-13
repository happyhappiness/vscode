static int fsck_handle_reflog_ent(unsigned char *osha1, unsigned char *nsha1,
		const char *email, unsigned long timestamp, int tz,
		const char *message, void *cb_data)
{
	const char *refname = cb_data;

	if (verbose)
		fprintf(stderr, "Checking reflog %s->%s\n",
			sha1_to_hex(osha1), sha1_to_hex(nsha1));

	fsck_handle_reflog_sha1(refname, osha1, 0);
	fsck_handle_reflog_sha1(refname, nsha1, timestamp);
	return 0;
}