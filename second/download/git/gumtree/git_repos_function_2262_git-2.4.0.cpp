static int check_if_different(struct trailer_item *in_tok,
			      struct trailer_item *arg_tok,
			      int check_all)
{
	enum action_where where = arg_tok->conf.where;
	do {
		if (!in_tok)
			return 1;
		if (same_trailer(in_tok, arg_tok))
			return 0;
		/*
		 * if we want to add a trailer after another one,
		 * we have to check those before this one
		 */
		in_tok = after_or_end(where) ? in_tok->previous : in_tok->next;
	} while (check_all);
	return 1;
}