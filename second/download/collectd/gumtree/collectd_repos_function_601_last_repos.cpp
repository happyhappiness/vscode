static int agg_instance_read(agg_instance_t *inst, cdtime_t t) /* {{{ */
{
  value_list_t vl = VALUE_LIST_INIT;

  /* Pre-set all the fields in the value list that will not change per
   * aggregation type (sum, average, ...). The struct will be re-used and must
   * therefore be dispatched using the "secure" function. */

  vl.time = t;
  vl.interval = 0;

  vl.meta = meta_data_create();
  if (vl.meta == NULL) {
    ERROR("aggregation plugin: meta_data_create failed.");
    return -1;
  }
  meta_data_add_boolean(vl.meta, "aggregation:created", 1);

  sstrncpy(vl.host, inst->ident.host, sizeof(vl.host));
  sstrncpy(vl.plugin, inst->ident.plugin, sizeof(vl.plugin));
  sstrncpy(vl.type, inst->ident.type, sizeof(vl.type));
  sstrncpy(vl.type_instance, inst->ident.type_instance,
           sizeof(vl.type_instance));

#define READ_FUNC(func, rate)                                                  \
  do {                                                                         \
    if (inst->state_##func != NULL) {                                          \
      agg_instance_read_func(inst, #func, rate, inst->state_##func, &vl,       \
                             inst->ident.plugin_instance, t);                  \
    }                                                                          \
  } while (0)

  pthread_mutex_lock(&inst->lock);

  READ_FUNC(num, (gauge_t)inst->num);

  /* All other aggregations are only defined when there have been any values
   * at all. */
  if (inst->num > 0) {
    READ_FUNC(sum, inst->sum);
    READ_FUNC(average, (inst->sum / ((gauge_t)inst->num)));
    READ_FUNC(min, inst->min);
    READ_FUNC(max, inst->max);
    READ_FUNC(stddev, sqrt((((gauge_t)inst->num) * inst->squares_sum) -
                           (inst->sum * inst->sum)) /
                          ((gauge_t)inst->num));
  }

  /* Reset internal state. */
  inst->num = 0;
  inst->sum = 0.0;
  inst->squares_sum = 0.0;
  inst->min = NAN;
  inst->max = NAN;

  pthread_mutex_unlock(&inst->lock);

  meta_data_destroy(vl.meta);
  vl.meta = NULL;

  return 0;
}