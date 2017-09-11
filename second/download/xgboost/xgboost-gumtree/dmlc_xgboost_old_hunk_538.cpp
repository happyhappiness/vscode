  fprintf(stderr, "%s\n", msg);
  exit(-1);
}
#else
// include declarations, some one must implement this
void HandleAssertError(const char *msg);
void HandleCheckError(const char *msg);
#endif

/*! \brief assert an condition is true, use this to handle debug information */
inline void Assert(bool exp, const char *fmt, ...) {
  if (!exp) {
    std::string msg(kErrorBuffer, '\0');
    va_list args;
    va_start(args, fmt);
    vsnprintf(&msg[0], kErrorBuffer, fmt, args);
    va_end(args);
    HandleAssertError(msg.c_str());
  }
