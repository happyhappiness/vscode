size_t latency_counter_get_num(latency_counter_t *lc) /* {{{ */
{
  if (lc == NULL)
    return 0;
  return lc->num;
}