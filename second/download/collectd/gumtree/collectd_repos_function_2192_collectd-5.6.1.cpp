int lookup_add (lookup_t *obj, /* {{{ */
    identifier_t const *ident, unsigned int group_by, void *user_class)
{
  by_type_entry_t *by_type = NULL;
  user_class_list_t *user_class_obj;

  by_type = lu_search_by_type (obj, ident->type, /* allocate = */ 1);
  if (by_type == NULL)
    return (-1);

  user_class_obj = calloc (1, sizeof (*user_class_obj));
  if (user_class_obj == NULL)
  {
    ERROR ("utils_vl_lookup: calloc failed.");
    return (ENOMEM);
  }
  pthread_mutex_init (&user_class_obj->entry.lock, /* attr = */ NULL);
  user_class_obj->entry.user_class = user_class;
  lu_copy_ident_to_match (&user_class_obj->entry.match, ident, group_by);
  user_class_obj->entry.user_obj_list = NULL;
  user_class_obj->next = NULL;

  return (lu_add_by_plugin (by_type, user_class_obj));
}