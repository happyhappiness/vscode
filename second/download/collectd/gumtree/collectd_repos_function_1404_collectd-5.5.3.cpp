static int compare_time (const void *v0, const void *v1) /* {{{ */
{
  const lcc_value_list_t *vl0 = v0;
  const lcc_value_list_t *vl1 = v1;

  if (vl0->time < vl1->time)
    return (-1);
  else if (vl0->time > vl1->time)
    return (1);
  else
    return (0);
}