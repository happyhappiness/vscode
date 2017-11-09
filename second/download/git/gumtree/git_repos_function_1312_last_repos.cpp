static void free_patch_list(struct patch *list)
{
	while (list) {
		struct patch *next = list->next;
		free_patch(list);
		list = next;
	}
}