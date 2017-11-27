static agg_instance_t *agg_instance_create(data_set_t const *ds, /* {{{ */
                                           value_list_t const *vl,
                                           aggregation_t *agg) {
  agg_instance_t *inst;

  DEBUG("aggregation plugin: Creating new instance.");

  inst = calloc(1, sizeof(*inst));
  if (inst == NULL) {
    ERROR("aggregation plugin: calloc() failed.");
    return NULL;
  }
  pthread_mutex_init(&inst->lock, /* attr = */ NULL);

  inst->ds_type = ds->ds[0].type;

  agg_instance_create_name(inst, vl, agg);

  inst->min = NAN;
  inst->max = NAN;

#define INIT_STATE(field)                                                      \
  do {                                                                         \
    inst->state_##field = NULL;                                                \
    if (agg->calc_##field) {                                                   \
      inst->state_##field = calloc(1, sizeof(*inst->state_##field));           \
      if (inst->state_##field == NULL) {                                       \
        agg_instance_destroy(inst);                                            \
        free(inst);                                                            \
        ERROR("aggregation plugin: calloc() failed.");                         \
        return NULL;                                                           \
      }                                                                        \
    }                                                                          \
  } while (0)

  INIT_STATE(num);
  INIT_STATE(sum);
  INIT_STATE(average);
  INIT_STATE(min);
  INIT_STATE(max);
  INIT_STATE(stddev);

#undef INIT_STATE

  pthread_mutex_lock(&agg_instance_list_lock);
  inst->next = agg_instance_list_head;
  agg_instance_list_head = inst;
  pthread_mutex_unlock(&agg_instance_list_lock);

  return inst;
}