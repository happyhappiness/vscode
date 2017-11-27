cdtime_t latency_counter_get_average (latency_counter_t *lc) /* {{{ */
{
  double average;

  if ((lc == NULL) || (lc->num == 0))
    return (0);

  average = CDTIME_T_TO_DOUBLE (lc->sum) / ((double) lc->num);
  return (DOUBLE_TO_CDTIME_T (average));
}