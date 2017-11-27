
static lcc_value_list_t *create_value_list (void) /* {{{ */
{
  lcc_value_list_t *vl;
  int host_num;

  vl = calloc (1, sizeof (*vl));
  if (vl == NULL)
  {
    fprintf (stderr, "calloc failed.\n");
    return (NULL);
  }

  vl->values = calloc (/* nmemb = */ 1, sizeof (*vl->values));
  if (vl->values == NULL)
  {
    fprintf (stderr, "calloc failed.\n");
    free (vl);
