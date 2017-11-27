static void lu_destroy_user_class_list (lookup_t *obj, /* {{{ */
    user_class_list_t *user_class_list)
{
  while (user_class_list != NULL)
  {
    user_class_list_t *next = user_class_list->next;

    if (obj->cb_free_class != NULL)
      obj->cb_free_class (user_class_list->entry.user_class);
    user_class_list->entry.user_class = NULL;

    lu_destroy_user_obj (obj, user_class_list->entry.user_obj_list);
    user_class_list->entry.user_obj_list = NULL;
    pthread_mutex_destroy (&user_class_list->entry.lock);

    sfree (user_class_list);
    user_class_list = next;
  }
}