static int parse_subjectrx_list (BUFFER *buf, BUFFER *s, unsigned long data, BUFFER *err)
{
  int rc;

  rc = parse_replace_list(buf, s, data, err);
  if (rc == 0)
    clear_subject_mods();
  return rc;
}