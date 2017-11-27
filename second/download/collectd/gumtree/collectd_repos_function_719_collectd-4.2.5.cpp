void oconfig_free (oconfig_item_t *ci)
{
  int i;

  if (ci->values != NULL)
    free (ci->values);

  for (i = 0; i < ci->children_num; i++)
    oconfig_free (ci->children + i);
}