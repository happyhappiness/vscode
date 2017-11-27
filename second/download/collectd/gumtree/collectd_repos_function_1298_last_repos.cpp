static void tcsv_metric_definition_destroy(void *arg) {
  metric_definition_t *md;
  metric_definition_t *next;

  md = arg;
  if (md == NULL)
    return;

  next = md->next;
  md->next = NULL;

  sfree(md->name);
  sfree(md->type);
  sfree(md->instance);
  sfree(md);

  tcsv_metric_definition_destroy(next);
}