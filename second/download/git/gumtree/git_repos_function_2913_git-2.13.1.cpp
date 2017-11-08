static struct trailer_item *trailer_from_arg(struct arg_item *arg_tok)
{
	struct trailer_item *new = xcalloc(sizeof(*new), 1);
	new->token = arg_tok->token;
	new->value = arg_tok->value;
	arg_tok->token = arg_tok->value = NULL;
	free_arg_item(arg_tok);
	return new;
}