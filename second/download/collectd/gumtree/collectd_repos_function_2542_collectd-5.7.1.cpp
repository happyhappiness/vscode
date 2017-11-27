int check_capability(int arg) /* {{{ */
{
  cap_value_t cap = (cap_value_t)arg;

  if (!CAP_IS_SUPPORTED(cap))
    return (-1);

  int have_cap = cap_get_bound(cap);
  if (have_cap != 1)
    return (-1);

  return (0);
}