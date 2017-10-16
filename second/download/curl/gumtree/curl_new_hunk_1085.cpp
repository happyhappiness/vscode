 ***************************************************************************/

#include "curl_setup.h"

CURLcode Curl_sendf(curl_socket_t sockfd, struct connectdata *,
                    const char *fmt, ...);
void Curl_infof(struct Curl_easy *, const char *fmt, ...);
void Curl_failf(struct Curl_easy *, const char *fmt, ...);

#if defined(CURL_DISABLE_VERBOSE_STRINGS)

#if defined(HAVE_VARIADIC_MACROS_C99)
#define infof(...)  Curl_nop_stmt
#elif defined(HAVE_VARIADIC_MACROS_GCC)
