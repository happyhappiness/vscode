static const char *msgnum(const struct am_state *state)
{
	static struct strbuf sb = STRBUF_INIT;

	strbuf_reset(&sb);
	strbuf_addf(&sb, "%0*d", state->prec, state->cur);

	return sb.buf;
}