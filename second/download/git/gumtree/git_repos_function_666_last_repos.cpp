static int do_config_from(struct config_source *top, config_fn_t fn, void *data)
{
	int ret;

	/* push config-file parsing state stack */
	top->prev = cf;
	top->linenr = 1;
	top->eof = 0;
	strbuf_init(&top->value, 1024);
	strbuf_init(&top->var, 1024);
	cf = top;

	ret = git_parse_source(fn, data);

	/* pop config-file parsing state stack */
	strbuf_release(&top->value);
	strbuf_release(&top->var);
	cf = top->prev;

	return ret;
}