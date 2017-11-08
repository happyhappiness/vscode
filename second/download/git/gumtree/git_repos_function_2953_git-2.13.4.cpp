static void add_arg_item(struct list_head *arg_head, char *tok, char *val,
			 const struct conf_info *conf)
{
	struct arg_item *new = xcalloc(sizeof(*new), 1);
	new->token = tok;
	new->value = val;
	duplicate_conf(&new->conf, conf);
	list_add_tail(&new->list, arg_head);
}