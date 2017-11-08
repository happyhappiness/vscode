static int already_written(struct bulk_checkin_state *state, unsigned char sha1[])
{
	int i;

	/* The object may already exist in the repository */
	if (has_sha1_file(sha1))
		return 1;

	/* Might want to keep the list sorted */
	for (i = 0; i < state->nr_written; i++)
		if (!hashcmp(state->written[i]->oid.hash, sha1))
			return 1;

	/* This is a new object we need to keep */
	return 0;
}