int lookup_search(lookup_t *obj, /* {{{ */
                  data_set_t const *ds, value_list_t const *vl) {
  by_type_entry_t *by_type = NULL;
  user_class_list_t *user_class_list = NULL;
  int retval = 0;
  int status;

  if ((obj == NULL) || (ds == NULL) || (vl == NULL))
    return (-EINVAL);

  by_type = lu_search_by_type(obj, vl->type, /* allocate = */ 0);
  if (by_type == NULL)
    return (0);

  status =
      c_avl_get(by_type->by_plugin_tree, vl->plugin, (void *)&user_class_list);
  if (status == 0) {
    status = lu_handle_user_class_list(obj, ds, vl, user_class_list);
    if (status < 0)
      return (status);
    retval += status;
  }

  if (by_type->wildcard_plugin_list != NULL) {
    status =
        lu_handle_user_class_list(obj, ds, vl, by_type->wildcard_plugin_list);
    if (status < 0)
      return (status);
    retval += status;
  }

  return (retval);
}