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