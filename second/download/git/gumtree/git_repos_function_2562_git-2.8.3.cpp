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