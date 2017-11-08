static int find_same_and_apply_arg(struct trailer_item **in_tok_first,
				   struct trailer_item **in_tok_last,
				   struct trailer_item *arg_tok)
{
	struct trailer_item *in_tok;
	struct trailer_item *on_tok;
	struct trailer_item *following_tok;

	enum action_where where = arg_tok->conf.where;
	int middle = (where == WHERE_AFTER) || (where == WHERE_BEFORE);
	int backwards = after_or_end(where);
	struct trailer_item *start_tok = backwards ? *in_tok_last : *in_tok_first;

	for (in_tok = start_tok; in_tok; in_tok = following_tok) {
		following_tok = backwards ? in_tok->previous : in_tok->next;
		if (!same_token(in_tok, arg_tok))
			continue;
		on_tok = middle ? in_tok : start_tok;
		apply_arg_if_exists(in_tok, arg_tok, on_tok,
				    in_tok_first, in_tok_last);
		return 1;
	}
	return 0;
}