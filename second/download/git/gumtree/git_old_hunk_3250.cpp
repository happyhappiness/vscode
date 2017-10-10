	for (i = strlen(s) - 1; i >= 0; i--)
		if (!isspace(s[i]))
			return s[i];
	return '\0';
}

static void print_tok_val(const char *tok, const char *val)
{
	char c = last_non_space_char(tok);
	if (!c)
		return;
	if (strchr(separators, c))
		printf("%s%s\n", tok, val);
	else
		printf("%s%c %s\n", tok, separators[0], val);
}

static void print_all(struct trailer_item *first, int trim_empty)
{
	struct trailer_item *item;
	for (item = first; item; item = item->next) {
		if (!trim_empty || strlen(item->value) > 0)
			print_tok_val(item->token, item->value);
	}
}

static void update_last(struct trailer_item **last)
{
	if (*last)
