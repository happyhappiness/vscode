static void apply_arg_if_exists(struct trailer_item *in_tok,
				struct trailer_item *arg_tok,
				struct trailer_item *on_tok,
				struct trailer_item **in_tok_first,
				struct trailer_item **in_tok_last)
{
	switch (arg_tok->conf.if_exists) {
	case EXISTS_DO_NOTHING:
		free_trailer_item(arg_tok);
		break;
	case EXISTS_REPLACE:
		apply_item_command(in_tok, arg_tok);
		add_arg_to_input_list(on_tok, arg_tok,
				      in_tok_first, in_tok_last);
		remove_from_list(in_tok, in_tok_first, in_tok_last);
		free_trailer_item(in_tok);
		break;
	case EXISTS_ADD:
		apply_item_command(in_tok, arg_tok);
		add_arg_to_input_list(on_tok, arg_tok,
				      in_tok_first, in_tok_last);
		break;
	case EXISTS_ADD_IF_DIFFERENT:
		apply_item_command(in_tok, arg_tok);
		if (check_if_different(in_tok, arg_tok, 1))
			add_arg_to_input_list(on_tok, arg_tok,
					      in_tok_first, in_tok_last);
		else
			free_trailer_item(arg_tok);
		break;
	case EXISTS_ADD_IF_DIFFERENT_NEIGHBOR:
		apply_item_command(in_tok, arg_tok);
		if (check_if_different(on_tok, arg_tok, 0))
			add_arg_to_input_list(on_tok, arg_tok,
					      in_tok_first, in_tok_last);
		else
			free_trailer_item(arg_tok);
		break;
	}
}