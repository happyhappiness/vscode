int state_printf (STATE *s, const char *fmt, ...)
{
  int rv;
  va_list ap;

  va_start (ap, fmt);
  rv = vfprintf (s->fpout, fmt, ap);
  va_end (ap);
  
  return rv;
}