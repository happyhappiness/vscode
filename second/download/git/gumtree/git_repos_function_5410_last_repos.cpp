static void write_author_script(const struct am_state *state)
{
	struct strbuf sb = STRBUF_INIT;

	strbuf_addstr(&sb, "GIT_AUTHOR_NAME=");
	sq_quote_buf(&sb, state->author_name);
	strbuf_addch(&sb, '\n');

	strbuf_addstr(&sb, "GIT_AUTHOR_EMAIL=");
	sq_quote_buf(&sb, state->author_email);
	strbuf_addch(&sb, '\n');

	strbuf_addstr(&sb, "GIT_AUTHOR_DATE=");
	sq_quote_buf(&sb, state->author_date);
	strbuf_addch(&sb, '\n');

	write_state_text(state, "author-script", sb.buf);

	strbuf_release(&sb);
}