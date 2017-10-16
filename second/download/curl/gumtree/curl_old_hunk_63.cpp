 * copies of the Software, and permit persons to whom the Software is
 * furnished to do so, under the terms of the COPYING file.
 *
 * This software is distributed on an "AS IS" basis, WITHOUT WARRANTY OF ANY
 * KIND, either express or implied.
 *
 * $Id: sendf.h,v 1.22 2004/01/07 09:19:35 bagder Exp $
 ***************************************************************************/

CURLcode Curl_sendf(int fd, struct connectdata *, const char *fmt, ...);
void Curl_infof(struct SessionHandle *, const char *fmt, ...);
void Curl_failf(struct SessionHandle *, const char *fmt, ...);

#define infof Curl_infof
#define failf Curl_failf

