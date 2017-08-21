 * The message SHALL NOT include any LF or CR.
 */

void Curl_failf(struct Curl_easy *data, const char *fmt, ...)
{
  va_list ap;
  size_t len;
