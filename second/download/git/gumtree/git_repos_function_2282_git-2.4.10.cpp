static void process_trailers_lists(struct trailer_item **in_tok_first,
				   struct trailer_item **in_tok_last,
				   struct trailer_item **arg_tok_first)
{
	struct trailer_item *arg_tok;
	struct trailer_item *next_arg;

	if (!*arg_tok_first)
		return;

	for (arg_tok = *arg_tok_first; arg_tok; arg_tok = next_arg) {
		int applied = 0;

		next_arg = arg_tok->next;
		remove_from_list(arg_tok, arg_tok_first, NULL);

		applied = find_same_and_apply_arg(in_tok_first,
						  in_tok_last,
						  arg_tok);

		if (!applied)
			apply_arg_if_missing(in_tok_first,
					     in_tok_last,
					     arg_tok);
	}
}