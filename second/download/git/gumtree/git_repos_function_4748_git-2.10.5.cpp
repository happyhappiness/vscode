static void add_name_limit(struct apply_state *state,
			   const char *name,
			   int exclude)
{
	struct string_list_item *it;

	it = string_list_append(&state->limit_by_name, name);
	it->util = exclude ? NULL : (void *) 1;
}