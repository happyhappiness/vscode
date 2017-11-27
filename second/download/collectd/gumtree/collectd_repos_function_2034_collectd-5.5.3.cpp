static by_type_entry_t *lu_search_by_type (lookup_t *obj, /* {{{ */
    char const *type, _Bool allocate_if_missing)
{
  by_type_entry_t *by_type;
  char *type_copy;
  int status;

  status = c_avl_get (obj->by_type_tree, type, (void *) &by_type);
  if (status == 0)
    return (by_type);

  if (!allocate_if_missing)
    return (NULL);

  type_copy = strdup (type);
  if (type_copy == NULL)
  {
    ERROR ("utils_vl_lookup: strdup failed.");
    return (NULL);
  }

  by_type = malloc (sizeof (*by_type));
  if (by_type == NULL)
  {
    ERROR ("utils_vl_lookup: malloc failed.");
    sfree (type_copy);
    return (NULL);
  }
  memset (by_type, 0, sizeof (*by_type));
  by_type->wildcard_plugin_list = NULL;
  
  by_type->by_plugin_tree = c_avl_create ((void *) strcmp);
  if (by_type->by_plugin_tree == NULL)
  {
    ERROR ("utils_vl_lookup: c_avl_create failed.");
    sfree (by_type);
    sfree (type_copy);
    return (NULL);
  }

  status = c_avl_insert (obj->by_type_tree,
      /* key = */ type_copy, /* value = */ by_type);
  assert (status <= 0); /* >0 => entry exists => race condition. */
  if (status != 0)
  {
    ERROR ("utils_vl_lookup: c_avl_insert failed.");
    c_avl_destroy (by_type->by_plugin_tree);
    sfree (by_type);
    sfree (type_copy);
    return (NULL);
  }
  
  return (by_type);
}