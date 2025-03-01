  *                                  _   _ ____  _
  *  Project                     ___| | | |  _ \| |
  *                             / __| | | | |_) | |
  *                            | (__| |_| |  _ <| |___
  *                             \___|\___/|_| \_\_____|
  *
- * Copyright (C) 1998 - 2004, Daniel Stenberg, <daniel@haxx.se>, et al.
+ * Copyright (C) 1998 - 2005, Daniel Stenberg, <daniel@haxx.se>, et al.
  *
  * This software is licensed as described in the file COPYING, which
  * you should have received as part of this distribution. The terms
  * are also available at http://curl.haxx.se/docs/copyright.html.
  *
  * You may opt to use, copy, modify, merge, publish, distribute and/or sell
  * copies of the Software, and permit persons to whom the Software is
  * furnished to do so, under the terms of the COPYING file.
  *
  * This software is distributed on an "AS IS" basis, WITHOUT WARRANTY OF ANY
  * KIND, either express or implied.
  *
- * $Id: sendf.h,v 1.29 2005/01/21 09:32:33 bagder Exp $
+ * $Id: sendf.h,v 1.30 2005/02/09 13:06:40 bagder Exp $
  ***************************************************************************/
 
 CURLcode Curl_sendf(curl_socket_t sockfd, struct connectdata *,
                     const char *fmt, ...);
 void Curl_infof(struct SessionHandle *, const char *fmt, ...);
 void Curl_failf(struct SessionHandle *, const char *fmt, ...);
