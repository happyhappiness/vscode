static void add_arg_to_input_list(struct trailer_item *on_tok,
				  struct arg_item *arg_tok)
{
	int aoe = after_or_end(arg_tok->conf.where);
	struct trailer_item *to_add = trailer_from_arg(arg_tok);
	if (aoe)
		list_add(&to_add->list, &on_tok->list);
	else
		list_add_tail(&to_add->list, &on_tok->list);
}