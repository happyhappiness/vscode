int fc_default_action(const data_set_t *ds, value_list_t *vl) /* {{{ */
{
  /* FIXME: Pass the meta-data to match targets here (when implemented). */
  return (fc_bit_write_invoke(ds, vl,
                              /* meta = */ NULL, /* user_data = */ NULL));
}