@@ -5,7 +5,7 @@
  *                            | (__| |_| |  _ <| |___
  *                             \___|\___/|_| \_\_____|
  *
- * Copyright (C) 1998 - 2014, Daniel Stenberg, <daniel@haxx.se>, et al.
+ * Copyright (C) 1998 - 2015, Daniel Stenberg, <daniel@haxx.se>, et al.
  *
  * This software is licensed as described in the file COPYING, which
  * you should have received as part of this distribution. The terms
@@ -26,14 +26,17 @@
 RECEIVING COOKIE INFORMATION
 ============================
 
-struct CookieInfo *cookie_init(char *file);
+struct CookieInfo *Curl_cookie_init(struct SessionHandle *data,
+                    const char *file, struct CookieInfo *inc, bool newsession);
 
         Inits a cookie struct to store data in a local file. This is always
         called before any cookies are set.
 
-int cookies_set(struct CookieInfo *cookie, char *cookie_line);
+struct Cookie *Curl_cookie_add(struct SessionHandle *data,
+                 struct CookieInfo *c, bool httpheader, char *lineptr,
+                 const char *domain, const char *path);
 
-        The 'cookie_line' parameter is a full "Set-cookie:" line as
+        The 'lineptr' parameter is a full "Set-cookie:" line as
         received from a server.
 
         The function need to replace previously stored lines that this new
@@ -47,8 +50,8 @@ int cookies_set(struct CookieInfo *cookie, char *cookie_line);
 SENDING COOKIE INFORMATION
 ==========================
 
-struct Cookies *cookie_getlist(struct CookieInfo *cookie,
-                               char *host, char *path, bool secure);
+struct Cookies *Curl_cookie_getlist(struct CookieInfo *cookie,
+                                    char *host, char *path, bool secure);
 
         For a given host and path, return a linked list of cookies that
         the client should send to the server if used now. The secure
@@ -81,44 +84,33 @@ Example set of cookies:
 
 #if !defined(CURL_DISABLE_HTTP) && !defined(CURL_DISABLE_COOKIES)
 
-#define _MPRINTF_REPLACE
-#include <curl/mprintf.h>
-
+#include "curl_printf.h"
 #include "urldata.h"
 #include "cookie.h"
 #include "strequal.h"
 #include "strtok.h"
 #include "sendf.h"
 #include "slist.h"
-#include "curl_memory.h"
 #include "share.h"
 #include "strtoofft.h"
 #include "rawstr.h"
 #include "curl_memrchr.h"
 #include "inet_pton.h"
 
-/* The last #include file should be: */
+/* The last #include files should be: */
+#include "curl_memory.h"
 #include "memdebug.h"
 
 static void freecookie(struct Cookie *co)
 {
-  if(co->expirestr)
-    free(co->expirestr);
-  if(co->domain)
-    free(co->domain);
-  if(co->path)
-    free(co->path);
-  if(co->spath)
-    free(co->spath);
-  if(co->name)
-    free(co->name);
-  if(co->value)
-    free(co->value);
-  if(co->maxage)
-    free(co->maxage);
-  if(co->version)
-    free(co->version);
-
+  free(co->expirestr);
+  free(co->domain);
+  free(co->path);
+  free(co->spath);
+  free(co->name);
+  free(co->value);
+  free(co->maxage);
+  free(co->version);
   free(co);
 }
 
@@ -233,11 +225,14 @@ static char *sanitize_cookie_path(const char *cookie_path)
     return NULL;
 
   /* some stupid site sends path attribute with '"'. */
+  len = strlen(new_path);
   if(new_path[0] == '\"') {
-    memmove((void *)new_path, (const void *)(new_path + 1), strlen(new_path));
+    memmove((void *)new_path, (const void *)(new_path + 1), len);
+    len--;
   }
-  if(new_path[strlen(new_path) - 1] == '\"') {
-    new_path[strlen(new_path) - 1] = 0x0;
+  if(len && (new_path[len - 1] == '\"')) {
+    new_path[len - 1] = 0x0;
+    len--;
   }
 
   /* RFC6265 5.2.4 The Path Attribute */
@@ -249,8 +244,7 @@ static char *sanitize_cookie_path(const char *cookie_path)
   }
 
   /* convert /hoge/ to /hoge */
-  len = strlen(new_path);
-  if(1 < len && new_path[len - 1] == '/') {
+  if(len && new_path[len - 1] == '/') {
     new_path[len - 1] = 0x0;
   }
 
@@ -259,17 +253,26 @@ static char *sanitize_cookie_path(const char *cookie_path)
 
 /*
  * Load cookies from all given cookie files (CURLOPT_COOKIEFILE).
+ *
+ * NOTE: OOM or cookie parsing failures are ignored.
  */
 void Curl_cookie_loadfiles(struct SessionHandle *data)
 {
   struct curl_slist *list = data->change.cookielist;
   if(list) {
     Curl_share_lock(data, CURL_LOCK_DATA_COOKIE, CURL_LOCK_ACCESS_SINGLE);
     while(list) {
-      data->cookies = Curl_cookie_init(data,
-                                       list->data,
-                                       data->cookies,
-                                       data->set.cookiesession);
+      struct CookieInfo *newcookies = Curl_cookie_init(data,
+                                        list->data,
+                                        data->cookies,
+                                        data->set.cookiesession);
+      if(!newcookies)
+        /* Failure may be due to OOM or a bad cookie; both are ignored
+         * but only the first should be
+         */
+        infof(data, "ignoring failed cookie_init for %s\n", list->data);
+      else
+        data->cookies = newcookies;
       list = list->next;
     }
     curl_slist_free_all(data->change.cookielist); /* clean up list */
@@ -286,8 +289,7 @@ void Curl_cookie_loadfiles(struct SessionHandle *data)
  */
 static void strstore(char **str, const char *newstr)
 {
-  if(*str)
-    free(*str);
+  free(*str);
   *str = strdup(newstr);
 }
 
@@ -351,6 +353,8 @@ static bool isip(const char *domain)
  * Be aware that sometimes we get an IP-only host name, and that might also be
  * a numerical IPv6 address.
  *
+ * Returns NULL on out of memory or invalid cookie. This is suboptimal,
+ * as they should be treated separately.
  ***************************************************************************/
 
 struct Cookie *
@@ -405,7 +409,7 @@ Curl_cookie_add(struct SessionHandle *data,
     do {
       /* we have a <what>=<this> pair or a stand-alone word here */
       name[0]=what[0]=0; /* init the buffers */
-      if(1 <= sscanf(ptr, "%" MAX_NAME_TXT "[^;\r\n =]=%"
+      if(1 <= sscanf(ptr, "%" MAX_NAME_TXT "[^;\r\n =] =%"
                      MAX_COOKIE_LINE_TXT "[^;\r\n]",
                      name, what)) {
         /* Use strstore() below to properly deal with received cookie
@@ -820,21 +824,13 @@ Curl_cookie_add(struct SessionHandle *data,
 
         /* then free all the old pointers */
         free(clist->name);
-        if(clist->value)
-          free(clist->value);
-        if(clist->domain)
-          free(clist->domain);
-        if(clist->path)
-          free(clist->path);
-        if(clist->spath)
-          free(clist->spath);
-        if(clist->expirestr)
-          free(clist->expirestr);
-
-        if(clist->version)
-          free(clist->version);
-        if(clist->maxage)
-          free(clist->maxage);
+        free(clist->value);
+        free(clist->domain);
+        free(clist->path);
+        free(clist->spath);
+        free(clist->expirestr);
+        free(clist->version);
+        free(clist->maxage);
 
         *clist = *co;  /* then store all the new data */
 
@@ -882,22 +878,26 @@ Curl_cookie_add(struct SessionHandle *data,
  *
  * If 'newsession' is TRUE, discard all "session cookies" on read from file.
  *
+ * Returns NULL on out of memory. Invalid cookies are ignored.
  ****************************************************************************/
 struct CookieInfo *Curl_cookie_init(struct SessionHandle *data,
                                     const char *file,
                                     struct CookieInfo *inc,
                                     bool newsession)
 {
   struct CookieInfo *c;
-  FILE *fp;
+  FILE *fp = NULL;
   bool fromfile=TRUE;
+  char *line = NULL;
 
   if(NULL == inc) {
     /* we didn't get a struct, create one */
     c = calloc(1, sizeof(struct CookieInfo));
     if(!c)
       return NULL; /* failed to get memory */
     c->filename = strdup(file?file:"none"); /* copy the name just in case */
+    if(!c->filename)
+      goto fail; /* failed to get memory */
   }
   else {
     /* we got an already existing one, use that */
@@ -914,40 +914,51 @@ struct CookieInfo *Curl_cookie_init(struct SessionHandle *data,
     fp = NULL;
   }
   else
-    fp = file?fopen(file, "r"):NULL;
+    fp = file?fopen(file, FOPEN_READTEXT):NULL;
 
   c->newsession = newsession; /* new session? */
 
   if(fp) {
     char *lineptr;
     bool headerline;
 
-    char *line = malloc(MAX_COOKIE_LINE);
-    if(line) {
-      while(fgets(line, MAX_COOKIE_LINE, fp)) {
-        if(checkprefix("Set-Cookie:", line)) {
-          /* This is a cookie line, get it! */
-          lineptr=&line[11];
-          headerline=TRUE;
-        }
-        else {
-          lineptr=line;
-          headerline=FALSE;
-        }
-        while(*lineptr && ISBLANK(*lineptr))
-          lineptr++;
-
-        Curl_cookie_add(data, c, headerline, lineptr, NULL, NULL);
+    line = malloc(MAX_COOKIE_LINE);
+    if(!line)
+      goto fail;
+    while(fgets(line, MAX_COOKIE_LINE, fp)) {
+      if(checkprefix("Set-Cookie:", line)) {
+        /* This is a cookie line, get it! */
+        lineptr=&line[11];
+        headerline=TRUE;
+      }
+      else {
+        lineptr=line;
+        headerline=FALSE;
       }
-      free(line); /* free the line buffer */
+      while(*lineptr && ISBLANK(*lineptr))
+        lineptr++;
+
+      Curl_cookie_add(data, c, headerline, lineptr, NULL, NULL);
     }
+    free(line); /* free the line buffer */
+
     if(fromfile)
       fclose(fp);
   }
 
   c->running = TRUE;          /* now, we're running */
 
   return c;
+
+fail:
+  free(line);
+  if(!inc)
+    /* Only clean up if we allocated it here, as the original could still be in
+     * use by a share handle */
+    Curl_cookie_cleanup(c);
+  if(fromfile && fp)
+    fclose(fp);
+  return NULL; /* out of memory */
 }
 
 /* sort this so that the longest path gets before the shorter path */
@@ -1127,16 +1138,14 @@ void Curl_cookie_clearall(struct CookieInfo *cookies)
 void Curl_cookie_freelist(struct Cookie *co, bool cookiestoo)
 {
   struct Cookie *next;
-  if(co) {
-    while(co) {
-      next = co->next;
-      if(cookiestoo)
-        freecookie(co);
-      else
-        free(co); /* we only free the struct since the "members" are all just
-                     pointed out in the main cookie list! */
-      co = next;
-    }
+  while(co) {
+    next = co->next;
+    if(cookiestoo)
+      freecookie(co);
+    else
+      free(co); /* we only free the struct since the "members" are all just
+                   pointed out in the main cookie list! */
+    co = next;
   }
 }
 
@@ -1183,23 +1192,14 @@ void Curl_cookie_clearsess(struct CookieInfo *cookies)
  *
  * Curl_cookie_cleanup()
  *
- * Free a "cookie object" previous created with cookie_init().
+ * Free a "cookie object" previous created with Curl_cookie_init().
  *
  ****************************************************************************/
 void Curl_cookie_cleanup(struct CookieInfo *c)
 {
-  struct Cookie *co;
-  struct Cookie *next;
   if(c) {
-    if(c->filename)
-      free(c->filename);
-    co = c->cookies;
-
-    while(co) {
-      next = co->next;
-      freecookie(co);
-      co = next;
-    }
+    free(c->filename);
+    Curl_cookie_freelist(c->cookies, TRUE);
     free(c); /* free the base struct as well */
   }
 }
@@ -1262,7 +1262,7 @@ static int cookie_output(struct CookieInfo *c, const char *dumphere)
     use_stdout=TRUE;
   }
   else {
-    out = fopen(dumphere, "w");
+    out = fopen(dumphere, FOPEN_WRITETEXT);
     if(!out)
       return 1; /* failure */
   }
@@ -1274,9 +1274,10 @@ static int cookie_output(struct CookieInfo *c, const char *dumphere)
           "# http://curl.haxx.se/docs/http-cookies.html\n"
           "# This file was generated by libcurl! Edit at your own risk.\n\n",
           out);
-    co = c->cookies;
 
-    while(co) {
+    for(co = c->cookies; co; co = co->next) {
+      if(!co->domain)
+        continue;
       format_ptr = get_netscape_format(co);
       if(format_ptr == NULL) {
         fprintf(out, "#\n# Fatal libcurl error\n");
@@ -1286,7 +1287,6 @@ static int cookie_output(struct CookieInfo *c, const char *dumphere)
       }
       fprintf(out, "%s\n", format_ptr);
       free(format_ptr);
-      co=co->next;
     }
   }
 
@@ -1307,10 +1307,9 @@ struct curl_slist *Curl_cookie_list(struct SessionHandle *data)
       (data->cookies->numcookies == 0))
     return NULL;
 
-  c = data->cookies->cookies;
-
-  while(c) {
-    /* fill the list with _all_ the cookies we know */
+  for(c = data->cookies->cookies; c; c = c->next) {
+    if(!c->domain)
+      continue;
     line = get_netscape_format(c);
     if(!line) {
       curl_slist_free_all(list);
@@ -1323,7 +1322,6 @@ struct curl_slist *Curl_cookie_list(struct SessionHandle *data)
       return NULL;
     }
     list = beg;
-    c = c->next;
   }
 
   return list;