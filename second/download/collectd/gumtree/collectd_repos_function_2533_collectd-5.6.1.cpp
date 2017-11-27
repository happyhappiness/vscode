static int format_zone (char *buffer, size_t buffer_size, struct tm const *tm) /* {{{ */
{
  char tmp[7];
  size_t sz;

  if ((buffer == NULL) || (buffer_size < 7))
    return EINVAL;

  sz = strftime (tmp, sizeof (tmp), "%z", tm);
  if (sz == 0)
    return ENOMEM;
  if (sz != 5)
  {
    DEBUG ("format_zone: strftime(\"%%z\") = \"%s\", want \"+hhmm\"", tmp);
    sstrncpy (buffer, tmp, buffer_size);
    return 0;
  }

  buffer[0] = tmp[0];
  buffer[1] = tmp[1];
  buffer[2] = tmp[2];
  buffer[3] = ':';
  buffer[4] = tmp[3];
  buffer[5] = tmp[4];
  buffer[6] = 0;

  return 0;
}