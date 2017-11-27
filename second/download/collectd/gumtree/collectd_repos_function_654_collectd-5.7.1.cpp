static void agg_lookup_free_class_callback(void *user_class) /* {{{ */
{
  agg_destroy((aggregation_t *)user_class);
}