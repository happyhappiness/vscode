 * \param msg error message
 */
inline void HandleCheckError(const char *msg) {
  throw std::runtime_error(msg);
}
inline void HandlePrint(const char *msg) {
  printf("%s", msg);
