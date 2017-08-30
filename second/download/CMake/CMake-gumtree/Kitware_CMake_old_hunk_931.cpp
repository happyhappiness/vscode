	/*
	 * Allocate our private state.
	 */
	state = (struct program_bidder *)calloc(sizeof (*state), 1);
	if (state == NULL)
		return (ARCHIVE_FATAL);
	state->cmd = strdup(cmd);
	if (signature != NULL && signature_len > 0) {
		state->signature_len = signature_len;
		state->signature = malloc(signature_len);
		memcpy(state->signature, signature, signature_len);
	}

	/*
	 * Fill in the bidder object.
	 */
	bidder->data = state;
	bidder->bid = program_bidder_bid;
	bidder->init = program_bidder_init;
	bidder->options = NULL;
	bidder->free = program_bidder_free;
	return (ARCHIVE_OK);
}

static int
program_bidder_free(struct archive_read_filter_bidder *self)
{
	struct program_bidder *state = (struct program_bidder *)self->data;
	free(state->cmd);
	free(state->signature);
	free(self->data);
	return (ARCHIVE_OK);
}

/*
 * If we do have a signature, bid only if that matches.
 *
