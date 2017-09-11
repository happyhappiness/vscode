  va_end(args);
  HandlePrint(msg.c_str());
}

/*! \brief assert an condition is true, use this to handle debug information */
inline void Assert(bool exp, const char *fmt, ...) {
