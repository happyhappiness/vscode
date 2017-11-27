static int ts_invoke_derive(const data_set_t *ds, value_list_t *vl, /* {{{ */
                            ts_data_t *data, int dsrc_index) {
  int64_t curr_derive;
  int status;
  int failure;

  /* Required meta data */
  int64_t prev_derive;
  char key_prev_derive[128];
  int64_t int_derive;
  char key_int_derive[128];
  double int_fraction;
  char key_int_fraction[128];

  curr_derive = (int64_t)vl->values[dsrc_index].derive;

  ssnprintf(key_prev_derive, sizeof(key_prev_derive),
            "target_scale[%p,%i]:prev_derive", (void *)data, dsrc_index);
  ssnprintf(key_int_derive, sizeof(key_int_derive),
            "target_scale[%p,%i]:int_derive", (void *)data, dsrc_index);
  ssnprintf(key_int_fraction, sizeof(key_int_fraction),
            "target_scale[%p,%i]:int_fraction", (void *)data, dsrc_index);

  prev_derive = curr_derive;
  int_derive = 0;
  int_fraction = 0.0;

  /* Query the meta data */
  failure = 0;

  status = uc_meta_data_get_signed_int(vl, key_prev_derive, &prev_derive);
  if (status != 0)
    failure++;

  status = uc_meta_data_get_signed_int(vl, key_int_derive, &int_derive);
  if (status != 0)
    failure++;

  status = uc_meta_data_get_double(vl, key_int_fraction, &int_fraction);
  if (status != 0)
    failure++;

  if (failure == 0) {
    int64_t difference;
    double rate;

    /* Calcualte the rate */
    difference = curr_derive - prev_derive;
    rate = ((double)difference) / CDTIME_T_TO_DOUBLE(vl->interval);

    /* Modify the rate. */
    if (!isnan(data->factor))
      rate *= data->factor;
    if (!isnan(data->offset))
      rate += data->offset;

    /* Calculate the internal derive. */
    int_fraction += (rate * CDTIME_T_TO_DOUBLE(vl->interval));
    if (int_fraction < 0.0) /* handle negative integer rounding correctly */
      difference = ((int64_t)int_fraction) - 1;
    else
      difference = (int64_t)int_fraction;
    int_fraction -= ((double)difference);
    int_derive += difference;

    assert(int_fraction >= 0.0);
    assert(int_fraction < 1.0);

    DEBUG("Target `scale': ts_invoke_derive: %" PRIu64 " -> %g -> %" PRIu64
          "(+%g)",
          curr_derive, rate, int_derive, int_fraction);
  } else /* (failure != 0) */
  {
    int_derive = 0;
    int_fraction = 0.0;
  }

  vl->values[dsrc_index].derive = (derive_t)int_derive;

  /* Update to the new derive value */
  uc_meta_data_add_signed_int(vl, key_prev_derive, curr_derive);
  uc_meta_data_add_signed_int(vl, key_int_derive, int_derive);
  uc_meta_data_add_double(vl, key_int_fraction, int_fraction);

  return (0);
}