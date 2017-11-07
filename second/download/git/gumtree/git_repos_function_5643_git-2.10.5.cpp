static void free_remote_ref_states(struct ref_states *states)
{
	string_list_clear(&states->new, 0);
	string_list_clear(&states->stale, 1);
	string_list_clear(&states->tracked, 0);
	string_list_clear(&states->heads, 0);
	string_list_clear_func(&states->push, clear_push_info);
}