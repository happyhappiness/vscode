static void *lu_create_user_obj (lookup_t *obj, /* {{{ */
    data_set_t const *ds, value_list_t const *vl,
    user_class_t *user_class)
{
  user_obj_t *user_obj;

  user_obj = malloc (sizeof (*user_obj));
  if (user_obj == NULL)
  {
    ERROR ("utils_vl_lookup: malloc failed.");
    return (NULL);
  }
  memset (user_obj, 0, sizeof (*user_obj));
  user_obj->next = NULL;

  user_obj->user_obj = obj->cb_user_class (ds, vl, user_class->user_class);
  if (user_obj->user_obj == NULL)
  {
    sfree (user_obj);
    WARNING("utils_vl_lookup: User-provided constructor failed.");
    return (NULL);
  }

#define COPY_FIELD(field, group_mask) do { \
  if (user_class->match.field.is_regex \
      && ((user_class->match.group_by & group_mask) == 0)) \
    sstrncpy (user_obj->ident.field, "/.*/", sizeof (user_obj->ident.field)); \
  else \
    sstrncpy (user_obj->ident.field, vl->field, sizeof (user_obj->ident.field)); \
} while (0)

  COPY_FIELD (host, LU_GROUP_BY_HOST);
  COPY_FIELD (plugin, LU_GROUP_BY_PLUGIN);
  COPY_FIELD (plugin_instance, LU_GROUP_BY_PLUGIN_INSTANCE);
  COPY_FIELD (type, 0);
  COPY_FIELD (type_instance, LU_GROUP_BY_TYPE_INSTANCE);

#undef COPY_FIELD

  if (user_class->user_obj_list == NULL)
  {
    user_class->user_obj_list = user_obj;
  }
  else
  {
    user_obj_t *last = user_class->user_obj_list;
    while (last->next != NULL)
      last = last->next;
    last->next = user_obj;
  }

  return (user_obj);
}