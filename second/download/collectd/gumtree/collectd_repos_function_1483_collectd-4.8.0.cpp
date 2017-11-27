static void lcc_response_free (lcc_response_t *res) /* {{{ */
{
  size_t i;

  if (res == NULL)
    return;

  for (i = 0; i < res->lines_num; i++)
    free (res->lines[i]);
  free (res->lines);
  res->lines = NULL;
}