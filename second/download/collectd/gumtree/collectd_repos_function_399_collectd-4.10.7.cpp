gauge_t *uc_get_rate (const data_set_t *ds, const value_list_t *vl)
{
  char name[6 * DATA_MAX_NAME_LEN];
  gauge_t *ret = NULL;
  size_t ret_num = 0;
  int status;

  if (FORMAT_VL (name, sizeof (name), vl) != 0)
  {
    ERROR ("utils_cache: uc_get_rate: FORMAT_VL failed.");
    return (NULL);
  }

  status = uc_get_rate_by_name (name, &ret, &ret_num);
  if (status != 0)
    return (NULL);

  /* This is important - the caller has no other way of knowing how many
   * values are returned. */
  if (ret_num != (size_t) ds->ds_num)
  {
    ERROR ("utils_cache: uc_get_rate: ds[%s] has %i values, "
	"but uc_get_rate_by_name returned %zu.",
	ds->type, ds->ds_num, ret_num);
    sfree (ret);
    return (NULL);
  }

  return (ret);
}