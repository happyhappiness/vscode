  *                                  _   _ ____  _
  *  Project                     ___| | | |  _ \| |
  *                             / __| | | | |_) | |
  *                            | (__| |_| |  _ <| |___
  *                             \___|\___/|_| \_\_____|
  *
- * Copyright (C) 1998 - 2006, Daniel Stenberg, <daniel@haxx.se>, et al.
+ * Copyright (C) 1998 - 2007, Daniel Stenberg, <daniel@haxx.se>, et al.
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
- * $Id: sendf.h,v 1.33 2006-10-27 03:47:58 yangtse Exp $
+ * $Id: sendf.h,v 1.40 2007-03-27 04:17:26 yangtse Exp $
  ***************************************************************************/
 
+#include "setup.h"
+
 CURLcode Curl_sendf(curl_socket_t sockfd, struct connectdata *,
                     const char *fmt, ...);
 void Curl_infof(struct SessionHandle *, const char *fmt, ...);
 void Curl_failf(struct SessionHandle *, const char *fmt, ...);
 
 #if defined(CURL_DISABLE_VERBOSE_STRINGS)
-#if defined(__GNUC__)
-/* This style of variable argument macros is a gcc extension */
-#define infof(x...) /*ignore*/
+
+#if defined(HAVE_VARIADIC_MACROS_C99)
+#define infof(...)  do { } while (0)
+#elif defined(HAVE_VARIADIC_MACROS_GCC)
+#define infof(x...)  do { } while (0)
 #else
-/* C99 compilers could use this if we could detect them */
-/*#define infof(...) */
-/* Cast the args to void to make them a noop, side effects notwithstanding */
 #define infof (void)
 #endif
-#else
+
+#else /* CURL_DISABLE_VERBOSE_STRINGS */
+
 #define infof Curl_infof
-#endif
+
+#endif /* CURL_DISABLE_VERBOSE_STRINGS */
+
 #define failf Curl_failf
 
 #define CLIENTWRITE_BODY   1
 #define CLIENTWRITE_HEADER 2
 #define CLIENTWRITE_BOTH   (CLIENTWRITE_BODY|CLIENTWRITE_HEADER)
 
