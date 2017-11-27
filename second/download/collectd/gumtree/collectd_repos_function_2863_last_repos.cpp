static void plugin_value_list_free(value_list_t *vl) /* {{{ */
{
  if (vl == NULL)
    return;

  meta_data_destroy(vl->meta);
  sfree(vl->values);
  sfree(vl);
}