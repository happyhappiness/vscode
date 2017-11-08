const char *git_user_agent_sanitized(void)
{
	static const char *agent = NULL;

	if (!agent) {
		struct strbuf buf = STRBUF_INIT;
		int i;

		strbuf_addstr(&buf, git_user_agent());
		strbuf_trim(&buf);
		for (i = 0; i < buf.len; i++) {
			if (buf.buf[i] <= 32 || buf.buf[i] >= 127)
				buf.buf[i] = '.';
		}
		agent = buf.buf;
	}

	return agent;
}