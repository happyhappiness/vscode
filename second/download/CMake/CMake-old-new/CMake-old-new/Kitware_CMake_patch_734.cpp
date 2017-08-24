@@ -1,25 +1,25 @@
-/*****************************************************************************
+/***************************************************************************
  *                                  _   _ ____  _     
  *  Project                     ___| | | |  _ \| |    
  *                             / __| | | | |_) | |    
  *                            | (__| |_| |  _ <| |___ 
  *                             \___|\___/|_| \_\_____|
  *
- * Copyright (C) 2002, Daniel Stenberg, <daniel@haxx.se>, et al.
- *
- * In order to be useful for every potential user, curl and libcurl are
- * dual-licensed under the MPL and the MIT/X-derivate licenses.
+ * Copyright (C) 1998 - 2002, Daniel Stenberg, <daniel@haxx.se>, et al.
  *
+ * This software is licensed as described in the file COPYING, which
+ * you should have received as part of this distribution. The terms
+ * are also available at http://curl.haxx.se/docs/copyright.html.
+ * 
  * You may opt to use, copy, modify, merge, publish, distribute and/or sell
  * copies of the Software, and permit persons to whom the Software is
- * furnished to do so, under the terms of the MPL or the MIT/X-derivate
- * licenses. You may pick one of these licenses.
+ * furnished to do so, under the terms of the COPYING file.
  *
  * This software is distributed on an "AS IS" basis, WITHOUT WARRANTY OF ANY
  * KIND, either express or implied.
  *
  * $Id$
- *****************************************************************************/
+ ***************************************************************************/
 
 #include "setup.h"
 
@@ -29,21 +29,17 @@
 #include <curl/curl.h>
 #include "urldata.h"
 
-char *curl_version(void)
-{
-  static char version[200];
-  char *ptr;
-  strcpy(version, LIBCURL_NAME " " LIBCURL_VERSION );
-  ptr=strchr(version, '\0');
-
 #ifdef USE_SSLEAY
+static void getssl_version(char *ptr, long *num)
+{
 
 #if (SSLEAY_VERSION_NUMBER >= 0x905000)
   {
     char sub[2];
     unsigned long ssleay_value;
     sub[1]='\0';
     ssleay_value=SSLeay();
+    *num = ssleay_value;
     if(ssleay_value < 0x906000) {
       ssleay_value=SSLEAY_VERSION_NUMBER;
       sub[0]='\0';
@@ -56,16 +52,17 @@ char *curl_version(void)
         sub[0]='\0';
     }
 
-    sprintf(ptr, " (OpenSSL %lx.%lx.%lx%s)",
+    sprintf(ptr, " OpenSSL/%lx.%lx.%lx%s",
             (ssleay_value>>28)&0xf,
             (ssleay_value>>20)&0xff,
             (ssleay_value>>12)&0xff,
             sub);
   }
 
 #else
+  *num = SSLEAY_VERSION_NUMBER;
 #if (SSLEAY_VERSION_NUMBER >= 0x900000)
-  sprintf(ptr, " (SSL %lx.%lx.%lx)",
+  sprintf(ptr, " OpenSSL/%lx.%lx.%lx",
           (SSLEAY_VERSION_NUMBER>>28)&0xff,
           (SSLEAY_VERSION_NUMBER>>20)&0xff,
           (SSLEAY_VERSION_NUMBER>>12)&0xf);
@@ -79,37 +76,128 @@ char *curl_version(void)
     else
       sub[0]='\0';
 
-    sprintf(ptr, " (SSL %x.%x.%x%s)",
+    sprintf(ptr, " SSL/%x.%x.%x%s",
             (SSLEAY_VERSION_NUMBER>>12)&0xff,
             (SSLEAY_VERSION_NUMBER>>8)&0xf,
             (SSLEAY_VERSION_NUMBER>>4)&0xf, sub);
   }
 #endif
 #endif
-  ptr=strchr(ptr, '\0');
+}
+
+#endif
+
+char *curl_version(void)
+{
+  static char version[200];
+  char *ptr;
+  long num;
+  strcpy(version, LIBCURL_NAME "/" LIBCURL_VERSION );
+  ptr=strchr(version, '\0');
+
+#ifdef USE_SSLEAY
+  getssl_version(ptr, &num);
+  ptr=strchr(version, '\0');
+#else
+  (void)num; /* no compiler warning please */
 #endif
 
-#if defined(KRB4) || defined(ENABLE_IPV6)
-  strcat(ptr, " (");
-  ptr+=2;
 #ifdef KRB4
-  sprintf(ptr, "krb4 ");
+  sprintf(ptr, " krb4");
   ptr += strlen(ptr);
 #endif
 #ifdef ENABLE_IPV6
-  sprintf(ptr, "ipv6 ");
+  sprintf(ptr, " ipv6");
   ptr += strlen(ptr);
 #endif
-  sprintf(ptr, "enabled)");
+#ifdef HAVE_LIBZ
+  sprintf(ptr, " zlib/%s", zlibVersion());
   ptr += strlen(ptr);
 #endif
 
-#ifdef USE_ZLIB
-  sprintf(ptr, " (zlib %s)", zlibVersion());
-  ptr += strlen(ptr);
+  return version;
+}
+
+/* data for curl_version_info */
+
+static const char *protocols[] = {
+#ifndef CURL_DISABLE_FTP
+  "ftp",
+#endif
+#ifndef CURL_DISABLE_GOPHER
+  "gopher",
+#endif
+#ifndef CURL_DISABLE_TELNET
+  "telnet",
+#endif
+#ifndef CURL_DISABLE_DICT
+  "dict",
+#endif
+#ifndef CURL_DISABLE_LDAP
+  "ldap",
+#endif
+#ifndef CURL_DISABLE_HTTP
+  "http",
+#endif
+#ifndef CURL_DISABLE_FILE
+  "file",
 #endif
 
-  return version;
+#ifdef USE_SSLEAY
+#ifndef CURL_DISABLE_HTTP
+  "https",
+#endif
+#ifndef CURL_DISABLE_FTP
+  "ftps",
+#endif
+#endif
+  NULL
+};
+
+static curl_version_info_data version_info = {
+  CURLVERSION_FIRST,
+  LIBCURL_VERSION,
+  LIBCURL_VERSION_NUM,
+  OS, /* as found by configure or set by hand at build-time */
+  0 /* features is 0 by default */
+#ifdef ENABLE_IPV6
+  | CURL_VERSION_IPV6
+#endif
+#ifdef KRB4
+  | CURL_VERSION_KERBEROS4
+#endif
+#ifdef USE_SSLEAY
+  | CURL_VERSION_SSL
+#endif
+#ifdef HAVE_LIBZ
+  | CURL_VERSION_LIBZ
+#endif
+  ,
+  NULL, /* ssl_version */
+  0,    /* ssl_version_num */
+  NULL, /* zlib_version */
+  protocols
+};
+
+curl_version_info_data *curl_version_info(CURLversion stamp)
+{
+#ifdef USE_SSLEAY
+  static char ssl_buffer[80];
+  long num;
+  getssl_version(ssl_buffer, &num);
+
+  version_info.ssl_version = ssl_buffer;
+  version_info.ssl_version_num = num;
+  /* SSL stuff is left zero if undefined */
+#endif
+
+#ifdef HAVE_LIBZ
+  version_info.libz_version = zlibVersion();
+  /* libz left NULL if non-existing */
+#endif
+  (void)stamp; /* avoid compiler warnings, we don't use this */
+
+  return &version_info;
 }
 
 /*