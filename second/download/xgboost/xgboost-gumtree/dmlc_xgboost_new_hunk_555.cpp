/*! \brief report error message, same as check */
inline void Error(const char *fmt, ...) {
  {
    std::string msg(kPrintBuffer, '\0');
    va_list args;
    va_start(args, fmt);
    vsnprintf(&msg[0], kPrintBuffer, fmt, args);
    va_end(args);
    HandleCheckError(msg.c_str());
  }
