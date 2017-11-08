static struct trailer_item *add_trailer_item(struct list_head *head, char *tok,
					     char *val)
{
	struct trailer_item *new = xcalloc(sizeof(*new), 1);
	new->token = tok;
	new->value = val;
	list_add_tail(&new->list, head);
	return new;
}