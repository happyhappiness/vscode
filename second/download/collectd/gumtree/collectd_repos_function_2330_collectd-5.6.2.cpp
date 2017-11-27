void c_complain_once(int level, c_complain_t *c, const char *format, ...) {
  va_list ap;

  if (c->complained_once)
    return;

  va_start(ap, format);
  if (vcomplain(level, c, format, ap))
    c->complained_once = 1;
  va_end(ap);
}