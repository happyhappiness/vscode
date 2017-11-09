static void apply_item_command(struct trailer_item *in_tok, struct arg_item *arg_tok)
{
	if (arg_tok->conf.command) {
		const char *arg;
		if (arg_tok->value && arg_tok->value[0]) {
			arg = arg_tok->value;
		} else {
			if (in_tok && in_tok->value)
				arg = xstrdup(in_tok->value);
			else
				arg = xstrdup("");
		}
		arg_tok->value = apply_command(arg_tok->conf.command, arg);
		free((char *)arg);
	}
}