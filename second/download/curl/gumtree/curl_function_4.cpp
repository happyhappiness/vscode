void infof(struct UrlData *data, char *fmt, ...)
{
  va_list ap;
  if(data->conf & CONF_VERBOSE) {
    va_start(ap, fmt);
    fputs("* ", stderr);
    vfprintf(stderr, fmt, ap);
    va_end(ap);
  }
}