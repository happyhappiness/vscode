inline void Error(const char *fmt, ...) {
  {
    std::string msg(kErrorBuffer, '\0');
    va_list args;
    va_start(args, fmt);
    vsnprintf(&msg[0], kErrorBuffer, fmt, args);
    va_end(args);
    HandleCheckError(msg.c_str());
  }
}