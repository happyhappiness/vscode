static int is_ansi (unsigned char *buf)
{
  while (*buf && (isdigit(*buf) || *buf == ';'))
    buf++;
  return (*buf == 'm');
}