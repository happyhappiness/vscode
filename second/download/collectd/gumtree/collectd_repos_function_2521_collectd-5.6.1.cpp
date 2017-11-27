void match_value_reset (cu_match_value_t *mv)
{
  if (mv == NULL)
    return;

  if (mv->ds_type & UTILS_MATCH_DS_TYPE_GAUGE)
  {
    mv->value.gauge = NAN;
    mv->values_num = 0;
  }
}