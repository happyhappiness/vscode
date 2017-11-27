static int swap_read(void) /* {{{ */
{
  struct kvm_swap data_s;
  int status;

  gauge_t used;
  gauge_t total;

  if (kvm_obj == NULL)
    return (-1);

  /* only one structure => only get the grand total, no details */
  status = kvm_getswapinfo(kvm_obj, &data_s, 1, 0);
  if (status == -1)
    return (-1);

  total = (gauge_t)data_s.ksw_total;
  used = (gauge_t)data_s.ksw_used;

  total *= (gauge_t)kvm_pagesize;
  used *= (gauge_t)kvm_pagesize;

  swap_submit_usage(NULL, used, total - used, NULL, NAN);

  return (0);
}