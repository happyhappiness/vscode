static void lu_destroy_by_type(lookup_t *obj, /* {{{ */
                               by_type_entry_t *by_type) {

  while (42) {
    char *plugin = NULL;
    user_class_list_t *user_class_list = NULL;
    int status;

    status = c_avl_pick(by_type->by_plugin_tree, (void *)&plugin,
                        (void *)&user_class_list);
    if (status != 0)
      break;

    DEBUG("utils_vl_lookup: lu_destroy_by_type: Destroying plugin \"%s\".",
          plugin);
    sfree(plugin);
    lu_destroy_user_class_list(obj, user_class_list);
  }

  c_avl_destroy(by_type->by_plugin_tree);
  by_type->by_plugin_tree = NULL;

  lu_destroy_user_class_list(obj, by_type->wildcard_plugin_list);
  by_type->wildcard_plugin_list = NULL;

  sfree(by_type);
}