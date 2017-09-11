const int kPrintBuffer = 1 << 12;

#ifndef RABIT_CUSTOMIZE_MSG_
/*! 
 * \brief handling of Assert error, caused by inappropriate input
 * \param msg error message 
 */
inline void HandleAssertError(const char *msg) {
  fprintf(stderr, "AssertError:%s\n", msg);
  exit(-1);
}
/*! 
 * \brief handling of Check error, caused by inappropriate input
 * \param msg error message 
 */
inline void HandleCheckError(const char *msg) {
  fprintf(stderr, "%s\n", msg);
