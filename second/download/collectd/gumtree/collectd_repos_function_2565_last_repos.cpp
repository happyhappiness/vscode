static void lcc_response_free(lcc_response_t *res) /* {{{ */
{
  if (res == NULL)
    return;

  for (size_t i = 0; i < res->lines_num; i++)
    free(res->lines[i]);
  free(res->lines);
  res->lines = NULL;
}