cdtime_t latency_counter_get_min (latency_counter_t *lc) /* {{{ */
{
  if (lc == NULL)
    return (0);
  return (lc->min);
}