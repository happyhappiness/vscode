static void record_ws_error(struct apply_state *state,
			    unsigned result,
			    const char *line,
			    int len,
			    int linenr)
{
	char *err;

	if (!result)
		return;

	state->whitespace_error++;
	if (state->squelch_whitespace_errors &&
	    state->squelch_whitespace_errors < state->whitespace_error)
		return;

	err = whitespace_error_string(result);
	fprintf(stderr, "%s:%d: %s.\n%.*s\n",
		state->patch_input_file, linenr, err, len, line);
	free(err);
}