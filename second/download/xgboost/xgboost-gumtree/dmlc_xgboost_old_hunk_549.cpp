  printf("%s", msg);
}
#else
// include declarations, some one must implement this
void HandleAssertError(const char *msg);
void HandleCheckError(const char *msg);
void HandlePrint(const char *msg);
#endif

/*! \brief printf, print message to the console */
inline void Printf(const char *fmt, ...) {
  std::string msg(kPrintBuffer, '\0');
  va_list args;
  va_start(args, fmt);
