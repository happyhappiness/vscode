void lookup_destroy (lookup_t *obj) /* {{{ */
{
  int status;

  if (obj == NULL)
    return;

  while (42)
  {
    char *type = NULL;
    by_type_entry_t *by_type = NULL;

    status = c_avl_pick (obj->by_type_tree, (void *) &type, (void *) &by_type);
    if (status != 0)
      break;

    DEBUG ("utils_vl_lookup: lookup_destroy: Destroying type \"%s\".", type);
    sfree (type);
    lu_destroy_by_type (obj, by_type);
  }

  c_avl_destroy (obj->by_type_tree);
  obj->by_type_tree = NULL;

  sfree (obj);
}