static void *agg_lookup_class_callback(/* {{{ */
                                       data_set_t const *ds,
                                       value_list_t const *vl,
                                       void *user_class) {
  return (agg_instance_create(ds, vl, (aggregation_t *)user_class));
}