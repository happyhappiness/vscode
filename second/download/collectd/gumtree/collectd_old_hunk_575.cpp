} /* oconfig_item_t *oconfig_parse_file */

oconfig_item_t *oconfig_clone (const oconfig_item_t *ci_orig)
{
  oconfig_item_t *ci_copy;

  ci_copy = (oconfig_item_t *) malloc (sizeof (*ci_copy));
  if (ci_copy == NULL)
  {
    fprintf (stderr, "malloc failed.\n");
    return (NULL);
  }
  memset (ci_copy, 0, sizeof (*ci_copy));
  ci_copy->values = NULL;
  ci_copy->parent = NULL;
  ci_copy->children = NULL;

  ci_copy->key = strdup (ci_orig->key);
  if (ci_copy->key == NULL)
