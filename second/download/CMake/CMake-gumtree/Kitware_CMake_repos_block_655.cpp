{
	struct archive_read *a = (struct archive_read *)_a;
	struct archive_read_filter_bidder *bidder;
	struct program_bidder *state;

	/*
	 * Get a bidder object from the read core.
	 */
	if (__archive_read_get_bidder(a, &bidder) != ARCHIVE_OK)
		return (ARCHIVE_FATAL);

	/*
	 * Allocate our private state.
	 */
	state = (struct program_bidder *)calloc(1, sizeof (*state));
	if (state == NULL)
		goto memerr;
	state->cmd = strdup(cmd);
	if (state->cmd == NULL)
		goto memerr;

	return set_bidder_signature(bidder, state, signature, signature_len);
memerr:
	free_state(state);
	archive_set_error(_a, ENOMEM, "Can't allocate memory");
	return (ARCHIVE_FATAL);
}