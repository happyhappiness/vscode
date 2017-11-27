static int ts_invoke_absolute(const data_set_t *ds, value_list_t *vl, /* {{{ */
                              ts_data_t *data, int dsrc_index) {
  uint64_t curr_absolute;
  double rate;
  int status;

  /* Required meta data */
  double int_fraction;
  char key_int_fraction[128];

  curr_absolute = (uint64_t)vl->values[dsrc_index].absolute;

  ssnprintf(key_int_fraction, sizeof(key_int_fraction),
            "target_scale[%p,%i]:int_fraction", (void *)data, dsrc_index);

  int_fraction = 0.0;

  /* Query the meta data */
  status = uc_meta_data_get_double(vl, key_int_fraction, &int_fraction);
  if (status != 0)
    int_fraction = 0.0;

  rate = ((double)curr_absolute) / CDTIME_T_TO_DOUBLE(vl->interval);

  /* Modify the rate. */
  if (!isnan(data->factor))
    rate *= data->factor;
  if (!isnan(data->offset))
    rate += data->offset;

  /* Calculate the new absolute. */
  int_fraction += (rate * CDTIME_T_TO_DOUBLE(vl->interval));
  curr_absolute = (uint64_t)int_fraction;
  int_fraction -= ((double)curr_absolute);

  vl->values[dsrc_index].absolute = (absolute_t)curr_absolute;

  /* Update to the new absolute value */
  uc_meta_data_add_double(vl, key_int_fraction, int_fraction);

  return (0);
}