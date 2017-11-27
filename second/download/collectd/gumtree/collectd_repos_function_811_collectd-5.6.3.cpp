static void copy_type_list(type_list_t *l1, type_list_t *l2) {
  type_t *last = NULL;

  for (type_t *ptr1 = l1->head, *ptr2 = l2->head; NULL != ptr1;
       ptr1 = ptr1->next, last = ptr2, ptr2 = ptr2->next) {
    if (NULL == ptr2) {
      ptr2 = smalloc(sizeof(*ptr2));
      ptr2->name = NULL;
      ptr2->next = NULL;

      if (NULL == last) {
        l2->head = ptr2;
      } else {
        last->next = ptr2;
      }

      l2->tail = ptr2;
    }

    if (NULL == ptr2->name) {
      ptr2->name = sstrdup(ptr1->name);
    }

    ptr2->value = ptr1->value;
    ptr1->value = 0;
  }
  return;
}