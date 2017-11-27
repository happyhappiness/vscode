void match_value_reset(cu_match_value_t *mv) {
  if (mv == NULL)
    return;

  /* Reset GAUGE metrics only and except GAUGE_PERSIST. */
  if ((mv->ds_type & UTILS_MATCH_DS_TYPE_GAUGE) &&
      !(mv->ds_type & UTILS_MATCH_CF_GAUGE_PERSIST)) {
    mv->value.gauge = NAN;
    mv->values_num = 0;
  }
}