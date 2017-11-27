static int swap_read(void) /* {{{ */
{
  sg_swap_stats *swap;

  swap = sg_get_swap_stats();
  if (swap == NULL)
    return (-1);

  swap_submit_usage(NULL, (gauge_t)swap->used, (gauge_t)swap->free, NULL, NAN);

  return (0);
}