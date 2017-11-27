static int lu_add_by_plugin(by_type_entry_t *by_type, /* {{{ */
                            user_class_list_t *user_class_list) {
  user_class_list_t *ptr = NULL;
  identifier_match_t const *match = &user_class_list->entry.match;

  /* Lookup user_class_list from the per-plugin structure. If this is the first
   * user_class to be added, the block returns immediately. Otherwise they will
   * set "ptr" to non-NULL. */
  if (match->plugin.is_regex) {
    if (by_type->wildcard_plugin_list == NULL) {
      by_type->wildcard_plugin_list = user_class_list;
      return (0);
    }

    ptr = by_type->wildcard_plugin_list;
  }    /* if (plugin is wildcard) */
  else /* (plugin is not wildcard) */
  {
    int status;

    status =
        c_avl_get(by_type->by_plugin_tree, match->plugin.str, (void *)&ptr);

    if (status != 0) /* plugin not yet in tree */
    {
      char *plugin_copy = strdup(match->plugin.str);

      if (plugin_copy == NULL) {
        ERROR("utils_vl_lookup: strdup failed.");
        sfree(user_class_list);
        return (ENOMEM);
      }

      status =
          c_avl_insert(by_type->by_plugin_tree, plugin_copy, user_class_list);
      if (status != 0) {
        ERROR("utils_vl_lookup: c_avl_insert(\"%s\") failed with status %i.",
              plugin_copy, status);
        sfree(plugin_copy);
        sfree(user_class_list);
        return (status);
      } else {
        return (0);
      }
    } /* if (plugin not yet in tree) */
  }   /* if (plugin is not wildcard) */

  assert(ptr != NULL);

  while (ptr->next != NULL)
    ptr = ptr->next;
  ptr->next = user_class_list;

  return (0);
}