static void oconfig_free_all(oconfig_item_t *ci) {
  if (ci == NULL)
    return;

  if (ci->key != NULL)
    free(ci->key);

  for (int i = 0; i < ci->values_num; i++)
    if ((ci->values[i].type == OCONFIG_TYPE_STRING) &&
        (NULL != ci->values[i].value.string))
      free(ci->values[i].value.string);

  if (ci->values != NULL)
    free(ci->values);

  for (int i = 0; i < ci->children_num; i++)
    oconfig_free_all(ci->children + i);

  if (ci->children != NULL)
    free(ci->children);
}