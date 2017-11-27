static void free_str_list(struct str_list *strs) /* {{{ */
{
	for (int i=0; i<strs->nb_strs; i++)
		free(strs->strs[i]);
	free(strs->strs);
}