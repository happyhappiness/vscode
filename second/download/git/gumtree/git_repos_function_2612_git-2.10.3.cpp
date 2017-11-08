static struct trailer_item *process_command_line_args(struct string_list *trailers)
{
	struct trailer_item *arg_tok_first = NULL;
	struct trailer_item *arg_tok_last = NULL;
	struct string_list_item *tr;
	struct trailer_item *item;

	/* Add a trailer item for each configured trailer with a command */
	for (item = first_conf_item; item; item = item->next) {
		if (item->conf.command) {
			struct trailer_item *new = new_trailer_item(item, NULL, NULL);
			add_trailer_item(&arg_tok_first, &arg_tok_last, new);
		}
	}

	/* Add a trailer item for each trailer on the command line */
	for_each_string_list_item(tr, trailers) {
		struct trailer_item *new = create_trailer_item(tr->string);
		add_trailer_item(&arg_tok_first, &arg_tok_last, new);
	}

	return arg_tok_first;
}