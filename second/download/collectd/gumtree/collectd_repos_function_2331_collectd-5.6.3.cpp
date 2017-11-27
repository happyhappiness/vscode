void c_complain(int level, c_complain_t *c, const char *format, ...) {
  va_list ap;

  va_start(ap, format);
  if (vcomplain(level, c, format, ap))
    c->complained_once = 1;
  va_end(ap);
}