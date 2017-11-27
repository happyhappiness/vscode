static user_obj_t *lu_find_user_obj(user_class_t *user_class, /* {{{ */
                                    value_list_t const *vl) {
  user_obj_t *ptr;

  for (ptr = user_class->user_obj_list; ptr != NULL; ptr = ptr->next) {
    if (user_class->match.host.is_regex &&
        (user_class->match.group_by & LU_GROUP_BY_HOST) &&
        (strcmp(vl->host, ptr->ident.host) != 0))
      continue;
    if (user_class->match.plugin.is_regex &&
        (user_class->match.group_by & LU_GROUP_BY_PLUGIN) &&
        (strcmp(vl->plugin, ptr->ident.plugin) != 0))
      continue;
    if (user_class->match.plugin_instance.is_regex &&
        (user_class->match.group_by & LU_GROUP_BY_PLUGIN_INSTANCE) &&
        (strcmp(vl->plugin_instance, ptr->ident.plugin_instance) != 0))
      continue;
    if (user_class->match.type_instance.is_regex &&
        (user_class->match.group_by & LU_GROUP_BY_TYPE_INSTANCE) &&
        (strcmp(vl->type_instance, ptr->ident.type_instance) != 0))
      continue;

    return (ptr);
  }

  return (NULL);
}