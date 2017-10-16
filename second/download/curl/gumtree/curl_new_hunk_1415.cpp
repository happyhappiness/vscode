 * furnished to do so, under the terms of the MPL or the MIT/X-derivate
 * licenses. You may pick one of these licenses.
 *
 * This software is distributed on an "AS IS" basis, WITHOUT WARRANTY OF ANY
 * KIND, either express or implied.
 *
 * $Id: sendf.h,v 1.13 2001/08/30 22:48:34 bagder Exp $
 *****************************************************************************/

size_t Curl_sendf(int fd, struct connectdata *, const char *fmt, ...);
void Curl_infof(struct SessionHandle *, const char *fmt, ...);
void Curl_failf(struct SessionHandle *, const char *fmt, ...);

#define infof Curl_infof
#define failf Curl_failf

struct send_buffer {
  char *buffer;
