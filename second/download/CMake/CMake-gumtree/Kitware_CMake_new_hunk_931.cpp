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



static int

program_bidder_free(struct archive_read_filter_bidder *self)

{

	struct program_bidder *state = (struct program_bidder *)self->data;



	free_state(state);

	return (ARCHIVE_OK);

}



static void

free_state(struct program_bidder *state)

{



	if (state) {

		free(state->cmd);

		free(state->signature);

		free(state);

	}

}



/*

 * If we do have a signature, bid only if that matches.

 *

