static struct patch *in_fn_table(struct apply_state *state, const char *name)
{
	struct string_list_item *item;

	if (name == NULL)
		return NULL;

	item = string_list_lookup(&state->fn_table, name);
	if (item != NULL)
		return (struct patch *)item->util;

	return NULL;
}