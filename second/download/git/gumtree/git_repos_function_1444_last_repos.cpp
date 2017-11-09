static int apply_option_parse_directory(const struct option *opt,
					const char *arg, int unset)
{
	struct apply_state *state = opt->value;
	strbuf_reset(&state->root);
	strbuf_addstr(&state->root, arg);
	strbuf_complete(&state->root, '/');
	return 0;
}