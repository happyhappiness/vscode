void XGBoostAssert_R(int exp, const char *fmt, ...) {
  char buf[1024];
  if (exp == 0) {
    va_list args;
    va_start(args, fmt);
    vsprintf(buf, fmt, args);
    va_end(args);
    error("AssertError:%s\n", buf);
  }
}
void XGBoostCheck_R(int exp, const char *fmt, ...) {
  char buf[1024];
  if (exp == 0) {
    va_list args;
    va_start(args, fmt);
    vsprintf(buf, fmt, args);
    va_end(args);
