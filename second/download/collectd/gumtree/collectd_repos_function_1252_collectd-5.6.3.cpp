static void tcsv_instance_definition_destroy(void *arg) {
  instance_definition_t *id;

  id = arg;
  if (id == NULL)
    return;

  if (id->tail != NULL)
    cu_tail_destroy(id->tail);
  id->tail = NULL;

  sfree(id->instance);
  sfree(id->path);
  sfree(id->metric_list);
  sfree(id);
}