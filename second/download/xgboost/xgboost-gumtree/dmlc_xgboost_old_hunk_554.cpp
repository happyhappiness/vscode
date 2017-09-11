/*!\brief same as assert, but this is intended to be used as message for user*/
inline void Check(bool exp, const char *fmt, ...) {
  if (!exp) {
    std::string msg(kErrorBuffer, '\0');
    va_list args;
    va_start(args, fmt);
    vsnprintf(&msg[0], kErrorBuffer, fmt, args);
    va_end(args);
    HandleCheckError(msg.c_str());
  }
