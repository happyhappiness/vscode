
  c_file = NULL;

  return (ret);
} /* oconfig_item_t *oconfig_parse_file */

void oconfig_free (oconfig_item_t *ci)
{
  int i;

  if (ci == NULL)
    return;
