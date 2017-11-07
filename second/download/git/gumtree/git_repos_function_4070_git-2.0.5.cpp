static void free_patch(struct patch *patch)
{
	free_fragment_list(patch->fragments);
	free(patch->def_name);
	free(patch->old_name);
	free(patch->new_name);
	free(patch->result);
	free(patch);
}