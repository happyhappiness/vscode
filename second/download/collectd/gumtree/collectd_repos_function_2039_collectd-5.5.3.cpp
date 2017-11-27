lookup_t *lookup_create (lookup_class_callback_t cb_user_class, /* {{{ */
    lookup_obj_callback_t cb_user_obj,
    lookup_free_class_callback_t cb_free_class,
    lookup_free_obj_callback_t cb_free_obj)
{
  lookup_t *obj = malloc (sizeof (*obj));
  if (obj == NULL)
  {
    ERROR ("utils_vl_lookup: malloc failed.");
    return (NULL);
  }
  memset (obj, 0, sizeof (*obj));

  obj->by_type_tree = c_avl_create ((void *) strcmp);
  if (obj->by_type_tree == NULL)
  {
    ERROR ("utils_vl_lookup: c_avl_create failed.");
    sfree (obj);
    return (NULL);
  }

  obj->cb_user_class = cb_user_class;
  obj->cb_user_obj = cb_user_obj;
  obj->cb_free_class = cb_free_class;
  obj->cb_free_obj = cb_free_obj;

  return (obj);
}