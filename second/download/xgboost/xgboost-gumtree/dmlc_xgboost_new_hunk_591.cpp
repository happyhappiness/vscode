namespace xgboost {
/*! \brief namespace for helper utils of the project */
namespace utils {
/*! \brief error message buffer length */
const int kErrorBuffer = 1 << 12;

#ifndef XGBOOST_CUSTOMIZE_ERROR_
/*! 
 * \brief handling of Assert error, caused by in-apropriate input
 * \param msg error message 
 */
inline void HandleAssertError(const char *msg) {
  fprintf(stderr, "AssertError:%s\n", msg);
  exit(-1);
}
/*! 
 * \brief handling of Check error, caused by in-apropriate input
 * \param msg error message 
 */
inline void HandleCheckError(const char *msg) {
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
}

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
}

/*! \brief report error message, same as check */
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

