			return s[i];
	return '\0';
}

static void print_tok_val(FILE *outfile, const char *tok, const char *val)
{
	char c = last_non_space_char(tok);
	if (!c)
		return;
	if (strchr(separators, c))
		fprintf(outfile, "%s%s\n", tok, val);
	else
		fprintf(outfile, "%s%c %s\n", tok, separators[0], val);
}

static void print_all(FILE *outfile, struct trailer_item *first, int trim_empty)
{
	struct trailer_item *item;
	for (item = first; item; item = item->next) {
		if (!trim_empty || strlen(item->value) > 0)
			print_tok_val(outfile, item->token, item->value);
	}
}

static void update_last(struct trailer_item **last)
{
	if (*last)
		while ((*last)->next != NULL)
			*last = (*last)->next;
}

static void update_first(struct trailer_item **first)
{
	if (*first)
		while ((*first)->previous != NULL)
			*first = (*first)->previous;
}

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

static void remove_from_list(struct trailer_item *item,
			     struct trailer_item **first,
			     struct trailer_item **last)
{
	struct trailer_item *next = item->next;
	struct trailer_item *previous = item->previous;

	if (next) {
		item->next->previous = previous;
		item->next = NULL;
	} else if (last)
		*last = previous;

	if (previous) {
		item->previous->next = next;
		item->previous = NULL;
	} else if (first)
		*first = next;
}

static struct trailer_item *remove_first(struct trailer_item **first)
{
	struct trailer_item *item = *first;
	*first = item->next;
	if (item->next) {
		item->next->previous = NULL;
		item->next = NULL;
	}
	return item;
}

static const char *apply_command(const char *command, const char *arg)
{
	struct strbuf cmd = STRBUF_INIT;
	struct strbuf buf = STRBUF_INIT;
	struct child_process cp = CHILD_PROCESS_INIT;
	const char *argv[] = {NULL, NULL};
	const char *result;

	strbuf_addstr(&cmd, command);
	if (arg)
		strbuf_replace(&cmd, TRAILER_ARG_STRING, arg);

	argv[0] = cmd.buf;
