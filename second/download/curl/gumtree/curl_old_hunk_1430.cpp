 * furnished to do so, under the terms of the MPL or the MIT/X-derivate
 * licenses. You may pick one of these licenses.
 *
 * This software is distributed on an "AS IS" basis, WITHOUT WARRANTY OF ANY
 * KIND, either express or implied.
 *
 * $Id: sendf.h,v 1.11 2001/01/31 13:54:13 bagder Exp $
 *****************************************************************************/

size_t Curl_sendf(int fd, struct connectdata *, char *fmt, ...);
void Curl_infof(struct UrlData *, char *fmt, ...);
void Curl_failf(struct UrlData *, char *fmt, ...);

#define infof Curl_infof
#define failf Curl_failf

struct send_buffer {
  char *buffer;
  long size_max;
  long size_used;
};
typedef struct send_buffer send_buffer;

#define CLIENTWRITE_BODY   1
#define CLIENTWRITE_HEADER 2
#define CLIENTWRITE_BOTH   (CLIENTWRITE_BODY|CLIENTWRITE_HEADER)
