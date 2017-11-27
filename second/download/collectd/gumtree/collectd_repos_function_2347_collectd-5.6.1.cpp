static void uc_check_range (const data_set_t *ds, cache_entry_t *ce)
{
  for (size_t i = 0; i < ds->ds_num; i++)
  {
    if (isnan (ce->values_gauge[i]))
      continue;
    else if (ce->values_gauge[i] < ds->ds[i].min)
      ce->values_gauge[i] = NAN;
    else if (ce->values_gauge[i] > ds->ds[i].max)
      ce->values_gauge[i] = NAN;
  }
}