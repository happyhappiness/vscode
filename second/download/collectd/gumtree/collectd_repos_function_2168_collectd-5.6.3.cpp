static int ts_invoke_gauge(const data_set_t *ds, value_list_t *vl, /* {{{ */
                           ts_data_t *data, int dsrc_index) {
  if (!isnan(data->factor))
    vl->values[dsrc_index].gauge *= data->factor;
  if (!isnan(data->offset))
    vl->values[dsrc_index].gauge += data->offset;

  return (0);
}