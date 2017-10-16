 * furnished to do so, under the terms of the MPL or the MIT/X-derivate
 * licenses. You may pick one of these licenses.
 *
 * This software is distributed on an "AS IS" basis, WITHOUT WARRANTY OF ANY
 * KIND, either express or implied.
 *
 * $Id: sendf.h,v 1.10 2001/01/25 12:20:30 bagder Exp $
 *****************************************************************************/

size_t Curl_sendf(int fd, struct connectdata *, char *fmt, ...);
void Curl_infof(struct UrlData *, char *fmt, ...);
void Curl_failf(struct UrlData *, char *fmt, ...);

