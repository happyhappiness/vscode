int uc_get_history (const data_set_t *ds, const value_list_t *vl,
    gauge_t *ret_history, size_t num_steps, size_t num_ds)
{
  char name[6 * DATA_MAX_NAME_LEN];

  if (FORMAT_VL (name, sizeof (name), vl) != 0)
  {
    ERROR ("utils_cache: uc_get_history: FORMAT_VL failed.");
    return (-1);
  }

  return (uc_get_history_by_name (name, ret_history, num_steps, num_ds));
}