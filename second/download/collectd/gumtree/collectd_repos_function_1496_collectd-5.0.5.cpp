static void udb_result_free (udb_result_t *r) /* {{{ */
{
  size_t i;

  if (r == NULL)
    return;

  sfree (r->type);

  for (i = 0; i < r->instances_num; i++)
    sfree (r->instances[i]);
  sfree (r->instances);

  for (i = 0; i < r->values_num; i++)
    sfree (r->values[i]);
  sfree (r->values);

  udb_result_free (r->next);

  sfree (r);
}