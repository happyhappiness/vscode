void git_config_push_parameter(const char *text)
{
	struct strbuf env = STRBUF_INIT;
	const char *old = getenv(CONFIG_DATA_ENVIRONMENT);
	if (old && *old) {
		strbuf_addstr(&env, old);
		strbuf_addch(&env, ' ');
	}
	sq_quote_buf(&env, text);
	setenv(CONFIG_DATA_ENVIRONMENT, env.buf, 1);
	strbuf_release(&env);
}