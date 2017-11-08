static void free_ref_list(struct ref_list *ref_list)
{
	int i;

	for (i = 0; i < ref_list->index; i++) {
		free(ref_list->list[i].name);
		free(ref_list->list[i].dest);
	}
	free(ref_list->list);
}