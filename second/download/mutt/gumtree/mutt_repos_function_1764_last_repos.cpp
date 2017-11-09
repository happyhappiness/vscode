static int parse_unsubjectrx_list (BUFFER *buf, BUFFER *s, unsigned long data, BUFFER *err)
{
  int rc;

  rc = parse_unreplace_list(buf, s, data, err);
  if (rc == 0)
    clear_subject_mods();
  return rc;
}