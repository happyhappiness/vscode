static void am_append_signoff(struct am_state *state)
{
	struct strbuf sb = STRBUF_INIT;

	strbuf_attach(&sb, state->msg, state->msg_len, state->msg_len);
	am_signoff(&sb);
	state->msg = strbuf_detach(&sb, &state->msg_len);
}