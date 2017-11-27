static derive_t vserver_get_sock_bytes(const char *s) {
  value_t v;
  int status;

  while (s[0] != '/')
    ++s;

  /* Remove '/' */
  ++s;

  status = parse_value(s, &v, DS_TYPE_DERIVE);
  if (status != 0)
    return (-1);
  return (v.derive);
}