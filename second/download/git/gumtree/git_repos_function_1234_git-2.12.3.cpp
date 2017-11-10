static void prepare_fn_table(struct apply_state *state, struct patch *patch)
{
	/*
	 * store information about incoming file deletion
	 */
	while (patch) {
		if ((patch->new_name == NULL) || (patch->is_rename)) {
			struct string_list_item *item;
			item = string_list_insert(&state->fn_table, patch->old_name);
			item->util = PATH_TO_BE_DELETED;
		}
		patch = patch->next;
	}
}