static void destroy_value_list (lcc_value_list_t *vl) /* {{{ */
{
  if (vl == NULL)
    return;

  free (vl->values);
  free (vl->values_types);
  free (vl);
}