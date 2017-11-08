static void apply_arg_if_missing(struct trailer_item **in_tok_first,
				 struct trailer_item **in_tok_last,
				 struct trailer_item *arg_tok)
{
	struct trailer_item **in_tok;
	enum action_where where;

	switch (arg_tok->conf.if_missing) {
	case MISSING_DO_NOTHING:
		free_trailer_item(arg_tok);
		break;
	case MISSING_ADD:
		where = arg_tok->conf.where;
		in_tok = after_or_end(where) ? in_tok_last : in_tok_first;
		apply_item_command(NULL, arg_tok);
		if (*in_tok) {
			add_arg_to_input_list(*in_tok, arg_tok,
					      in_tok_first, in_tok_last);
		} else {
			*in_tok_first = arg_tok;
			*in_tok_last = arg_tok;
		}
		break;
	}
}