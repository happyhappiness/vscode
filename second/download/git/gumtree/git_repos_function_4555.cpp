static void free_fragment_list(struct fragment *list)
{
	while (list) {
		struct fragment *next = list->next;
		if (list->free_patch)
			free((char *)list->patch);
		free(list);
		list = next;
	}
}