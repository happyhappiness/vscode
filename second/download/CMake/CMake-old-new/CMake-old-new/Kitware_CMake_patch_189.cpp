@@ -5,11 +5,11 @@
  *                            | (__| |_| |  _ <| |___
  *                             \___|\___/|_| \_\_____|
  *
- * Copyright (C) 1998 - 2015, Daniel Stenberg, <daniel@haxx.se>, et al.
+ * Copyright (C) 1998 - 2016, Daniel Stenberg, <daniel@haxx.se>, et al.
  *
  * This software is licensed as described in the file COPYING, which
  * you should have received as part of this distribution. The terms
- * are also available at http://curl.haxx.se/docs/copyright.html.
+ * are also available at https://curl.haxx.se/docs/copyright.html.
  *
  * You may opt to use, copy, modify, merge, publish, distribute and/or sell
  * copies of the Software, and permit persons to whom the Software is
@@ -26,13 +26,13 @@
 RECEIVING COOKIE INFORMATION
 ============================
 
-struct CookieInfo *Curl_cookie_init(struct SessionHandle *data,
+struct CookieInfo *Curl_cookie_init(struct Curl_easy *data,
                     const char *file, struct CookieInfo *inc, bool newsession);
 
         Inits a cookie struct to store data in a local file. This is always
         called before any cookies are set.
 
-struct Cookie *Curl_cookie_add(struct SessionHandle *data,
+struct Cookie *Curl_cookie_add(struct Curl_easy *data,
                  struct CookieInfo *c, bool httpheader, char *lineptr,
                  const char *domain, const char *path);
 
@@ -84,7 +84,10 @@ Example set of cookies:
 
 #if !defined(CURL_DISABLE_HTTP) && !defined(CURL_DISABLE_COOKIES)
 
-#include "curl_printf.h"
+#ifdef USE_LIBPSL
+# include <libpsl.h>
+#endif
+
 #include "urldata.h"
 #include "cookie.h"
 #include "strequal.h"
@@ -97,7 +100,8 @@ Example set of cookies:
 #include "curl_memrchr.h"
 #include "inet_pton.h"
 
-/* The last #include files should be: */
+/* The last 3 #include files should be in this order */
+#include "curl_printf.h"
 #include "curl_memory.h"
 #include "memdebug.h"
 
@@ -256,7 +260,7 @@ static char *sanitize_cookie_path(const char *cookie_path)
  *
  * NOTE: OOM or cookie parsing failures are ignored.
  */
-void Curl_cookie_loadfiles(struct SessionHandle *data)
+void Curl_cookie_loadfiles(struct Curl_easy *data)
 {
   struct curl_slist *list = data->change.cookielist;
   if(list) {
@@ -305,7 +309,7 @@ static void remove_expired(struct CookieInfo *cookies)
   pv = NULL;
   while(co) {
     nx = co->next;
-    if((co->expirestr || co->maxage) && co->expires < now) {
+    if(co->expires && co->expires < now) {
       if(co == cookies->cookies) {
         cookies->cookies = co->next;
       }
@@ -358,7 +362,7 @@ static bool isip(const char *domain)
  ***************************************************************************/
 
 struct Cookie *
-Curl_cookie_add(struct SessionHandle *data,
+Curl_cookie_add(struct Curl_easy *data,
                 /* The 'data' pointer here may be NULL at times, and thus
                    must only be used very carefully for things that can deal
                    with data being NULL. Such as infof() and similar */
@@ -379,6 +383,10 @@ Curl_cookie_add(struct SessionHandle *data,
   bool replace_old = FALSE;
   bool badcookie = FALSE; /* cookies are good by default. mmmmm yummy */
 
+#ifdef USE_LIBPSL
+  const psl_ctx_t *psl;
+#endif
+
 #ifdef CURL_DISABLE_VERBOSE_STRINGS
   (void)data;
 #endif
@@ -409,7 +417,7 @@ Curl_cookie_add(struct SessionHandle *data,
     do {
       /* we have a <what>=<this> pair or a stand-alone word here */
       name[0]=what[0]=0; /* init the buffers */
-      if(1 <= sscanf(ptr, "%" MAX_NAME_TXT "[^;\r\n =] =%"
+      if(1 <= sscanf(ptr, "%" MAX_NAME_TXT "[^;\r\n=] =%"
                      MAX_COOKIE_LINE_TXT "[^;\r\n]",
                      name, what)) {
         /* Use strstore() below to properly deal with received cookie
@@ -419,15 +427,24 @@ Curl_cookie_add(struct SessionHandle *data,
         bool done = FALSE;
         bool sep;
         size_t len=strlen(what);
-        const char *endofn = &ptr[ strlen(name) ];
-
-        /* skip trailing spaces in name */
-        while(*endofn && ISBLANK(*endofn))
-          endofn++;
+        size_t nlen = strlen(name);
+        const char *endofn = &ptr[ nlen ];
 
         /* name ends with a '=' ? */
         sep = (*endofn == '=')?TRUE:FALSE;
 
+        if(nlen) {
+          endofn--; /* move to the last character */
+          if(ISBLANK(*endofn)) {
+            /* skip trailing spaces in name */
+            while(*endofn && ISBLANK(*endofn) && nlen) {
+              endofn--;
+              nlen--;
+            }
+            name[nlen]=0; /* new end of name */
+          }
+        }
+
         /* Strip off trailing whitespace from the 'what' */
         while(len && ISBLANK(what[len-1])) {
           what[len-1]=0;
@@ -439,7 +456,16 @@ Curl_cookie_add(struct SessionHandle *data,
         while(*whatptr && ISBLANK(*whatptr))
           whatptr++;
 
-        if(!len) {
+        if(!co->name && sep) {
+          /* The very first name/value pair is the actual cookie name */
+          co->name = strdup(name);
+          co->value = strdup(whatptr);
+          if(!co->name || !co->value) {
+            badcookie = TRUE;
+            break;
+          }
+        }
+        else if(!len) {
           /* this was a "<name>=" with no content, and we must allow
              'secure' and 'httponly' specified this weirdly */
           done = TRUE;
@@ -533,14 +559,6 @@ Curl_cookie_add(struct SessionHandle *data,
             break;
           }
         }
-        else if(!co->name) {
-          co->name = strdup(name);
-          co->value = strdup(whatptr);
-          if(!co->name || !co->value) {
-            badcookie = TRUE;
-            break;
-          }
-        }
         /*
           else this is the second (or more) name we don't know
           about! */
@@ -777,6 +795,21 @@ Curl_cookie_add(struct SessionHandle *data,
   /* at first, remove expired cookies */
   remove_expired(c);
 
+#ifdef USE_LIBPSL
+  /* Check if the domain is a Public Suffix and if yes, ignore the cookie.
+     This needs a libpsl compiled with builtin data. */
+  if(domain && co->domain && !isip(co->domain)) {
+    if(((psl = psl_builtin()) != NULL)
+        && !psl_is_cookie_domain_acceptable(psl, domain, co->domain)) {
+      infof(data,
+            "cookie '%s' dropped, domain '%s' must not set cookies for '%s'\n",
+            co->name, domain, co->domain);
+      freecookie(co);
+      return NULL;
+    }
+  }
+#endif
+
   clist = c->cookies;
   replace_old = FALSE;
   while(clist) {
@@ -880,7 +913,7 @@ Curl_cookie_add(struct SessionHandle *data,
  *
  * Returns NULL on out of memory. Invalid cookies are ignored.
  ****************************************************************************/
-struct CookieInfo *Curl_cookie_init(struct SessionHandle *data,
+struct CookieInfo *Curl_cookie_init(struct Curl_easy *data,
                                     const char *file,
                                     struct CookieInfo *inc,
                                     bool newsession)
@@ -1247,6 +1280,7 @@ static int cookie_output(struct CookieInfo *c, const char *dumphere)
   struct Cookie *co;
   FILE *out;
   bool use_stdout=FALSE;
+  char *format_ptr;
 
   if((NULL == c) || (0 == c->numcookies))
     /* If there are no known cookies, we don't write or even create any
@@ -1267,27 +1301,23 @@ static int cookie_output(struct CookieInfo *c, const char *dumphere)
       return 1; /* failure */
   }
 
-  if(c) {
-    char *format_ptr;
+  fputs("# Netscape HTTP Cookie File\n"
+        "# https://curl.haxx.se/docs/http-cookies.html\n"
+        "# This file was generated by libcurl! Edit at your own risk.\n\n",
+        out);
 
-    fputs("# Netscape HTTP Cookie File\n"
-          "# http://curl.haxx.se/docs/http-cookies.html\n"
-          "# This file was generated by libcurl! Edit at your own risk.\n\n",
-          out);
-
-    for(co = c->cookies; co; co = co->next) {
-      if(!co->domain)
-        continue;
-      format_ptr = get_netscape_format(co);
-      if(format_ptr == NULL) {
-        fprintf(out, "#\n# Fatal libcurl error\n");
-        if(!use_stdout)
-          fclose(out);
-        return 1;
-      }
-      fprintf(out, "%s\n", format_ptr);
-      free(format_ptr);
+  for(co = c->cookies; co; co = co->next) {
+    if(!co->domain)
+      continue;
+    format_ptr = get_netscape_format(co);
+    if(format_ptr == NULL) {
+      fprintf(out, "#\n# Fatal libcurl error\n");
+      if(!use_stdout)
+        fclose(out);
+      return 1;
     }
+    fprintf(out, "%s\n", format_ptr);
+    free(format_ptr);
   }
 
   if(!use_stdout)
@@ -1296,7 +1326,7 @@ static int cookie_output(struct CookieInfo *c, const char *dumphere)
   return 0;
 }
 
-struct curl_slist *Curl_cookie_list(struct SessionHandle *data)
+struct curl_slist *Curl_cookie_list(struct Curl_easy *data)
 {
   struct curl_slist *list = NULL;
   struct curl_slist *beg;
@@ -1327,7 +1357,7 @@ struct curl_slist *Curl_cookie_list(struct SessionHandle *data)
   return list;
 }
 
-void Curl_flush_cookies(struct SessionHandle *data, int cleanup)
+void Curl_flush_cookies(struct Curl_easy *data, int cleanup)
 {
   if(data->set.str[STRING_COOKIEJAR]) {
     if(data->change.cookielist) {