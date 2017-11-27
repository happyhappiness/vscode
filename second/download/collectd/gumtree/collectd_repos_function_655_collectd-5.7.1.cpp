static void agg_lookup_free_obj_callback(void *user_obj) /* {{{ */
{
  agg_instance_destroy((agg_instance_t *)user_obj);
}