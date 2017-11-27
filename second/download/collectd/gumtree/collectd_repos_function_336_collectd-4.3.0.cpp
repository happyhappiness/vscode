static void type_list_incr (type_list_t *list, char *name, int incr)
{
	if (NULL == list->head) {
		list->head = (type_t *)smalloc (sizeof (type_t));

		list->head->name  = sstrdup (name);
		list->head->value = incr;
		list->head->next  = NULL;

		list->tail = list->head;
	}
	else {
		type_t *ptr;

		for (ptr = list->head; NULL != ptr; ptr = ptr->next) {
			if (0 == strcmp (name, ptr->name))
				break;
		}

		if (NULL == ptr) {
			list->tail->next = (type_t *)smalloc (sizeof (type_t));
			list->tail = list->tail->next;

			list->tail->name  = sstrdup (name);
			list->tail->value = incr;
			list->tail->next  = NULL;
		}
		else {
			ptr->value += incr;
		}
	}
	return;
}