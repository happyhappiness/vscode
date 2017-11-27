static void lu_destroy_user_class_list (lookup_t *obj, /* {{{ */
    user_class_list_t *user_class_list)
{
  while (user_class_list != NULL)
  {
    user_class_list_t *next = user_class_list->next;

    if (obj->cb_free_class != NULL)
      obj->cb_free_class (user_class_list->entry.user_class);
    user_class_list->entry.user_class = NULL;

#define CLEAR_FIELD(field) do { \
    if (user_class_list->entry.match.field.is_regex) { \
      regfree (&user_class_list->entry.match.field.regex); \
      user_class_list->entry.match.field.is_regex = 0; \
    } \
} while (0)

    CLEAR_FIELD (host);
    CLEAR_FIELD (plugin);
    CLEAR_FIELD (plugin_instance);
    CLEAR_FIELD (type);
    CLEAR_FIELD (type_instance);

#undef CLEAR_FIELD

    lu_destroy_user_obj (obj, user_class_list->entry.user_obj_list);
    user_class_list->entry.user_obj_list = NULL;
    pthread_mutex_destroy (&user_class_list->entry.lock);

    sfree (user_class_list);
    user_class_list = next;
  }
}