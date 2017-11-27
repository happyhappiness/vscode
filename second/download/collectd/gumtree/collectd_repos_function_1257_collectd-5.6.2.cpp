static int tcsv_shutdown(void) {
  tcsv_metric_definition_destroy(metric_head);
  metric_head = NULL;

  return (0);
}