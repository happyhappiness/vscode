static void type_list_incr(type_list_t *list, char *name, int incr) {
  if (list->head == NULL) {
    list->head = smalloc(sizeof(*list->head));

    list->head->name = sstrdup(name);
    list->head->value = incr;
    list->head->next = NULL;

    list->tail = list->head;
  } else {
    type_t *ptr;

    for (ptr = list->head; NULL != ptr; ptr = ptr->next) {
      if (strcmp(name, ptr->name) == 0)
        break;
    }

    if (ptr == NULL) {
      list->tail->next = smalloc(sizeof(*list->tail->next));
      list->tail = list->tail->next;

      list->tail->name = sstrdup(name);
      list->tail->value = incr;
      list->tail->next = NULL;
    } else {
      ptr->value += incr;
    }
  }
  return;
}