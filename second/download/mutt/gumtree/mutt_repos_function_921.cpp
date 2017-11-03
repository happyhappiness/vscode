rfc1524_entry *rfc1524_new_entry(void)
{
  return (rfc1524_entry *)safe_calloc(1, sizeof(rfc1524_entry));
}