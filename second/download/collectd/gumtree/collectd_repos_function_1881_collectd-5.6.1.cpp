static void udb_result_free (udb_result_t *r) /* {{{ */
{
  if (r == NULL)
    return;

  sfree (r->type);
  sfree (r->instance_prefix);

  for (size_t i = 0; i < r->instances_num; i++)
    sfree (r->instances[i]);
  sfree (r->instances);

  for (size_t i = 0; i < r->values_num; i++)
    sfree (r->values[i]);
  sfree (r->values);

  for (size_t i = 0; i < r->metadata_num; i++)
    sfree (r->metadata[i]);
  sfree (r->metadata);

  udb_result_free (r->next);

  sfree (r);
}