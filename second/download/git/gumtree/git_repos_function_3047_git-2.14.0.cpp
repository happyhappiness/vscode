static void apply_arg_if_missing(struct list_head *head,
				 struct arg_item *arg_tok)
{
	enum action_where where;
	struct trailer_item *to_add;

	switch (arg_tok->conf.if_missing) {
	case MISSING_DO_NOTHING:
		free_arg_item(arg_tok);
		break;
	case MISSING_ADD:
		where = arg_tok->conf.where;
		apply_item_command(NULL, arg_tok);
		to_add = trailer_from_arg(arg_tok);
		if (after_or_end(where))
			list_add_tail(&to_add->list, head);
		else
			list_add(&to_add->list, head);
	}
}