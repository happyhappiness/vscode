	default:
		die("BUG: trailer.c: unhandled type %d", type);
	}
	return 0;
}

static int parse_trailer(struct strbuf *tok, struct strbuf *val, const char *trailer)
{
	size_t len;
	struct strbuf seps = STRBUF_INIT;
	strbuf_addstr(&seps, separators);
	strbuf_addch(&seps, '=');
	len = strcspn(trailer, seps.buf);
	strbuf_release(&seps);
	if (len == 0) {
		int l = strlen(trailer);
		while (l > 0 && isspace(trailer[l - 1]))
			l--;
		return error(_("empty trailer token in trailer '%.*s'"), l, trailer);
	}
	if (len < strlen(trailer)) {
		strbuf_add(tok, trailer, len);
		strbuf_trim(tok);
		strbuf_addstr(val, trailer + len + 1);
		strbuf_trim(val);
	} else {
		strbuf_addstr(tok, trailer);
		strbuf_trim(tok);
	}
	return 0;
}

static const char *token_from_item(struct trailer_item *item, char *tok)
{
	if (item->conf.key)
		return item->conf.key;
	if (tok)
		return tok;
	return item->conf.name;
}

static struct trailer_item *new_trailer_item(struct trailer_item *conf_item,
					     char *tok, char *val)
{
	struct trailer_item *new = xcalloc(sizeof(*new), 1);
	new->value = val ? val : xstrdup("");

	if (conf_item) {
		duplicate_conf(&new->conf, &conf_item->conf);
		new->token = xstrdup(token_from_item(conf_item, tok));
		free(tok);
	} else {
		duplicate_conf(&new->conf, &default_conf_info);
		new->token = tok;
	}

	return new;
}

static int token_matches_item(const char *tok, struct trailer_item *item, int tok_len)
{
	if (!strncasecmp(tok, item->conf.name, tok_len))
		return 1;
	return item->conf.key ? !strncasecmp(tok, item->conf.key, tok_len) : 0;
}

static struct trailer_item *create_trailer_item(const char *string)
{
	struct strbuf tok = STRBUF_INIT;
	struct strbuf val = STRBUF_INIT;
	struct trailer_item *item;
	int tok_len;

	if (parse_trailer(&tok, &val, string))
		return NULL;

	tok_len = token_len_without_separator(tok.buf, tok.len);

	/* Lookup if the token matches something in the config */
	for (item = first_conf_item; item; item = item->next) {
		if (token_matches_item(tok.buf, item, tok_len))
			return new_trailer_item(item,
						strbuf_detach(&tok, NULL),
						strbuf_detach(&val, NULL));
	}

	return new_trailer_item(NULL,
				strbuf_detach(&tok, NULL),
				strbuf_detach(&val, NULL));
}

static void add_trailer_item(struct trailer_item **first,
			     struct trailer_item **last,
			     struct trailer_item *new)
{
	if (!new)
		return;
	if (!*last) {
		*first = new;
		*last = new;
	} else {
		(*last)->next = new;
		new->previous = *last;
		*last = new;
	}
}

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

static struct strbuf **read_input_file(const char *file)
{
	struct strbuf **lines;
	struct strbuf sb = STRBUF_INIT;
