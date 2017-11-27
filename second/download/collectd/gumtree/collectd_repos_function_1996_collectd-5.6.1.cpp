static void cpy_unregister_list(cpy_callback_t **list_head) {
	cpy_callback_t *cur, *next;
	for (cur = *list_head; cur; cur = next) {
		next = cur->next;
		cpy_destroy_user_data(cur);
	}
	*list_head = NULL;
}