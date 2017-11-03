static int addr_is_local (ADDRESS *a)
{
  return (a->intl_checked && !a->is_intl);
}