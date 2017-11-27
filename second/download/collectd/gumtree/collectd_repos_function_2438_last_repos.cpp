static int lu_handle_user_class(lookup_t *obj, /* {{{ */
                                data_set_t const *ds, value_list_t const *vl,
                                user_class_t *user_class) {
  user_obj_t *user_obj;
  int status;

  assert(strcmp(vl->type, user_class->match.type.str) == 0);
  assert(user_class->match.plugin.is_regex ||
         (strcmp(vl->plugin, user_class->match.plugin.str)) == 0);

  if (!lu_part_matches(&user_class->match.type_instance, vl->type_instance) ||
      !lu_part_matches(&user_class->match.plugin_instance,
                       vl->plugin_instance) ||
      !lu_part_matches(&user_class->match.plugin, vl->plugin) ||
      !lu_part_matches(&user_class->match.host, vl->host))
    return 1;

  pthread_mutex_lock(&user_class->lock);
  user_obj = lu_find_user_obj(user_class, vl);
  if (user_obj == NULL) {
    /* call lookup_class_callback_t() and insert into the list of user objects.
     */
    user_obj = lu_create_user_obj(obj, ds, vl, user_class);
    if (user_obj == NULL) {
      pthread_mutex_unlock(&user_class->lock);
      return -1;
    }
  }
  pthread_mutex_unlock(&user_class->lock);

  status = obj->cb_user_obj(ds, vl, user_class->user_class, user_obj->user_obj);
  if (status != 0) {
    ERROR("utils_vl_lookup: The user object callback failed with status %i.",
          status);
    /* Returning a negative value means: abort! */
    if (status < 0)
      return status;
    else
      return 1;
  }

  return 0;
}