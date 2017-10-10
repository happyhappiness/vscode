	default:
		die("BUG: trailer.c: unhandled type %d", type);
	}
	return 0;
}

static const char *token_from_item(struct arg_item *item, char *tok)
{
	if (item->conf.key)
		return item->conf.key;
	if (tok)
		return tok;
	return item->conf.name;
}

static int token_matches_item(const char *tok, struct arg_item *item, int tok_len)
{
	if (!strncasecmp(tok, item->conf.name, tok_len))
		return 1;
	return item->conf.key ? !strncasecmp(tok, item->conf.key, tok_len) : 0;
}

/*
 * Return the location of the first separator in line, or -1 if there is no
 * separator.
 */
static int find_separator(const char *line, const char *separators)
{
	int loc = strcspn(line, separators);
	if (!line[loc])
		return -1;
	return loc;
}

/*
 * Obtain the token, value, and conf from the given trailer.
 *
 * separator_pos must not be 0, since the token cannot be an empty string.
 *
 * If separator_pos is -1, interpret the whole trailer as a token.
 */
static void parse_trailer(struct strbuf *tok, struct strbuf *val,
			 const struct conf_info **conf, const char *trailer,
			 int separator_pos)
{
	struct arg_item *item;
	int tok_len;
	struct list_head *pos;

	if (separator_pos != -1) {
		strbuf_add(tok, trailer, separator_pos);
		strbuf_trim(tok);
		strbuf_addstr(val, trailer + separator_pos + 1);
		strbuf_trim(val);
	} else {
		strbuf_addstr(tok, trailer);
		strbuf_trim(tok);
	}

	/* Lookup if the token matches something in the config */
	tok_len = token_len_without_separator(tok->buf, tok->len);
	if (conf)
		*conf = &default_conf_info;
	list_for_each(pos, &conf_head) {
		item = list_entry(pos, struct arg_item, list);
		if (token_matches_item(tok->buf, item, tok_len)) {
			char *tok_buf = strbuf_detach(tok, NULL);
			if (conf)
				*conf = &item->conf;
			strbuf_addstr(tok, token_from_item(item, tok_buf));
			free(tok_buf);
			break;
		}
	}
}

static struct trailer_item *add_trailer_item(struct list_head *head, char *tok,
					     char *val)
{
	struct trailer_item *new = xcalloc(sizeof(*new), 1);
	new->token = tok;
	new->value = val;
	list_add_tail(&new->list, head);
	return new;
}

static void add_arg_item(struct list_head *arg_head, char *tok, char *val,
			 const struct conf_info *conf)
{
	struct arg_item *new = xcalloc(sizeof(*new), 1);
	new->token = tok;
	new->value = val;
	duplicate_conf(&new->conf, conf);
	list_add_tail(&new->list, arg_head);
}

static void process_command_line_args(struct list_head *arg_head,
				      struct string_list *trailers)
{
	struct string_list_item *tr;
	struct arg_item *item;
	struct strbuf tok = STRBUF_INIT;
	struct strbuf val = STRBUF_INIT;
	const struct conf_info *conf;
	struct list_head *pos;

	/*
	 * In command-line arguments, '=' is accepted (in addition to the
	 * separators that are defined).
	 */
	char *cl_separators = xstrfmt("=%s", separators);

	/* Add an arg item for each configured trailer with a command */
	list_for_each(pos, &conf_head) {
		item = list_entry(pos, struct arg_item, list);
		if (item->conf.command)
			add_arg_item(arg_head,
				     xstrdup(token_from_item(item, NULL)),
				     xstrdup(""),
				     &item->conf);
	}

	/* Add an arg item for each trailer on the command line */
	for_each_string_list_item(tr, trailers) {
		int separator_pos = find_separator(tr->string, cl_separators);
		if (separator_pos == 0) {
			struct strbuf sb = STRBUF_INIT;
			strbuf_addstr(&sb, tr->string);
			strbuf_trim(&sb);
			error(_("empty trailer token in trailer '%.*s'"),
			      (int) sb.len, sb.buf);
			strbuf_release(&sb);
		} else {
			parse_trailer(&tok, &val, &conf, tr->string,
				      separator_pos);
			add_arg_item(arg_head,
				     strbuf_detach(&tok, NULL),
				     strbuf_detach(&val, NULL),
				     conf);
		}
	}

	free(cl_separators);
}

static struct strbuf **read_input_file(const char *file)
{
	struct strbuf **lines;
	struct strbuf sb = STRBUF_INIT;
