static void add_arg_to_input_list(struct trailer_item *on_tok,
				  struct trailer_item *arg_tok,
				  struct trailer_item **first,
				  struct trailer_item **last)
{
	if (after_or_end(arg_tok->conf.where)) {
		arg_tok->next = on_tok->next;
		on_tok->next = arg_tok;
		arg_tok->previous = on_tok;
		if (arg_tok->next)
			arg_tok->next->previous = arg_tok;
		update_last(last);
	} else {
		arg_tok->previous = on_tok->previous;
		on_tok->previous = arg_tok;
		arg_tok->next = on_tok;
		if (arg_tok->previous)
			arg_tok->previous->next = arg_tok;
		update_first(first);
	}
}