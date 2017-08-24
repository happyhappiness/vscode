@@ -5,7 +5,7 @@
  *                            | (__| |_| |  _ <| |___
  *                             \___|\___/|_| \_\_____|
  *
- * Copyright (C) 1998 - 2004, Daniel Stenberg, <daniel@haxx.se>, et al.
+ * Copyright (C) 1998 - 2007, Daniel Stenberg, <daniel@haxx.se>, et al.
  *
  * This software is licensed as described in the file COPYING, which
  * you should have received as part of this distribution. The terms
@@ -80,25 +80,30 @@ Example set of cookies:
 
 #include "setup.h"
 
-#ifndef CURL_DISABLE_HTTP
+#if !defined(CURL_DISABLE_HTTP) && !defined(CURL_DISABLE_COOKIES)
 
 #include <stdlib.h>
 #include <string.h>
-#include <ctype.h>
+
+#define _MPRINTF_REPLACE /* without this on windows OS we get undefined reference to snprintf */
+#include <curl/mprintf.h>
 
 #include "urldata.h"
 #include "cookie.h"
-#include "getdate.h"
 #include "strequal.h"
 #include "strtok.h"
 #include "sendf.h"
-#include "curl_memory.h"
+#include "memory.h"
+#include "share.h"
+#include "strtoofft.h"
 
 /* The last #include file should be: */
 #ifdef CURLDEBUG
 #include "memdebug.h"
 #endif
 
+#define my_isspace(x) ((x == ' ') || (x == '\t'))
+
 static void freecookie(struct Cookie *co)
 {
   if(co->expirestr)
@@ -111,6 +116,10 @@ static void freecookie(struct Cookie *co)
     free(co->name);
   if(co->value)
     free(co->value);
+  if(co->maxage)
+    free(co->maxage);
+  if(co->version)
+    free(co->version);
 
   free(co);
 }
@@ -126,6 +135,27 @@ static bool tailmatch(const char *little, const char *bigone)
   return (bool)strequal(little, bigone+biglen-littlelen);
 }
 
+/*
+ * Load cookies from all given cookie files (CURLOPT_COOKIEFILE).
+ */
+void Curl_cookie_loadfiles(struct SessionHandle *data)
+{
+  struct curl_slist *list = data->change.cookielist;
+  if(list) {
+    Curl_share_lock(data, CURL_LOCK_DATA_COOKIE, CURL_LOCK_ACCESS_SINGLE);
+    while(list) {
+      data->cookies = Curl_cookie_init(data,
+                                       list->data,
+                                       data->cookies,
+                                       data->set.cookiesession);
+      list = list->next;
+    }
+    Curl_share_unlock(data, CURL_LOCK_DATA_COOKIE);
+    curl_slist_free_all(data->change.cookielist); /* clean up list */
+    data->change.cookielist = NULL; /* don't do this again! */
+  }
+}
+
 /****************************************************************************
  *
  * Curl_cookie_add()
@@ -156,7 +186,7 @@ Curl_cookie_add(struct SessionHandle *data,
   struct Cookie *co;
   struct Cookie *lastc=NULL;
   time_t now = time(NULL);
-  bool replace_old;
+  bool replace_old = FALSE;
   bool badcookie = FALSE; /* cookies are good by default. mmmmm yummy */
 
   /* First, alloc and init a new struct for it */
@@ -176,7 +206,7 @@ Curl_cookie_add(struct SessionHandle *data,
 
     semiptr=strchr(lineptr, ';'); /* first, find a semicolon */
 
-    while(*lineptr && isspace((int)*lineptr))
+    while(*lineptr && my_isspace(*lineptr))
       lineptr++;
 
     ptr = lineptr;
@@ -199,14 +229,14 @@ Curl_cookie_add(struct SessionHandle *data,
 
           /* Strip off trailing whitespace from the 'what' */
           size_t len=strlen(what);
-          while(len && isspace((int)what[len-1])) {
+          while(len && my_isspace(what[len-1])) {
             what[len-1]=0;
             len--;
           }
 
           /* Skip leading whitespace from the 'what' */
           whatptr=what;
-          while(isspace((int)*whatptr)) {
+          while(my_isspace(*whatptr)) {
             whatptr++;
           }
 
@@ -305,7 +335,7 @@ Curl_cookie_add(struct SessionHandle *data,
               break;
             }
             co->expires =
-              atoi((*co->maxage=='\"')?&co->maxage[1]:&co->maxage[0]) + now;
+              atoi((*co->maxage=='\"')?&co->maxage[1]:&co->maxage[0]) + (long)now;
           }
           else if(strequal("expires", name)) {
             co->expirestr=strdup(whatptr);
@@ -348,7 +378,7 @@ Curl_cookie_add(struct SessionHandle *data,
       }
 
       ptr=semiptr+1;
-      while(ptr && *ptr && isspace((int)*ptr))
+      while(ptr && *ptr && my_isspace(*ptr))
         ptr++;
       semiptr=strchr(ptr, ';'); /* now, find the next semicolon */
 
@@ -466,7 +496,7 @@ Curl_cookie_add(struct SessionHandle *data,
         co->secure = (bool)strequal(ptr, "TRUE");
         break;
       case 4:
-        co->expires = atoi(ptr);
+        co->expires = curlx_strtoofft(ptr, NULL, 10);
         break;
       case 5:
         co->name = strdup(ptr);
@@ -647,6 +677,10 @@ struct CookieInfo *Curl_cookie_init(struct SessionHandle *data,
     fp = stdin;
     fromfile=FALSE;
   }
+  else if(file && !*file) {
+    /* points to a "" string */
+    fp = NULL;
+  }
   else
     fp = file?fopen(file, "r"):NULL;
 
@@ -668,7 +702,7 @@ struct CookieInfo *Curl_cookie_init(struct SessionHandle *data,
           lineptr=line;
           headerline=FALSE;
         }
-        while(*lineptr && isspace((int)*lineptr))
+        while(*lineptr && my_isspace(*lineptr))
           lineptr++;
 
         Curl_cookie_add(data, c, headerline, lineptr, NULL, NULL);
@@ -699,68 +733,85 @@ struct CookieInfo *Curl_cookie_init(struct SessionHandle *data,
 struct Cookie *Curl_cookie_getlist(struct CookieInfo *c,
                                    char *host, char *path, bool secure)
 {
-   struct Cookie *newco;
-   struct Cookie *co;
-   time_t now = time(NULL);
-   struct Cookie *mainco=NULL;
-
-   if(!c || !c->cookies)
-      return NULL; /* no cookie struct or no cookies in the struct */
-
-   co = c->cookies;
-
-   while(co) {
-     /* only process this cookie if it is not expired or had no expire
-        date AND that if the cookie requires we're secure we must only
-        continue if we are! */
-     if( (co->expires<=0 || (co->expires> now)) &&
-         (co->secure?secure:TRUE) ) {
-
-       /* now check if the domain is correct */
-       if(!co->domain ||
-          (co->tailmatch && tailmatch(co->domain, host)) ||
-          (!co->tailmatch && strequal(host, co->domain)) ) {
-         /* the right part of the host matches the domain stuff in the
-            cookie data */
-
-         /* now check the left part of the path with the cookies path
-            requirement */
-         if(!co->path ||
-            checkprefix(co->path, path) ) {
-
-           /* and now, we know this is a match and we should create an
-              entry for the return-linked-list */
-
-           newco = (struct Cookie *)malloc(sizeof(struct Cookie));
-           if(newco) {
-             /* first, copy the whole source cookie: */
-             memcpy(newco, co, sizeof(struct Cookie));
-
-             /* then modify our next */
-             newco->next = mainco;
-
-             /* point the main to us */
-             mainco = newco;
-           }
-           else {
-              /* failure, clear up the allocated chain and return NULL */
-             while(mainco) {
-               co = mainco->next;
-               free(mainco);
-               mainco = co;
-             }
-
-             return NULL;
-           }
-         }
-       }
-     }
-     co = co->next;
-   }
-
-   return mainco; /* return the new list */
+  struct Cookie *newco;
+  struct Cookie *co;
+  time_t now = time(NULL);
+  struct Cookie *mainco=NULL;
+
+  if(!c || !c->cookies)
+    return NULL; /* no cookie struct or no cookies in the struct */
+
+  co = c->cookies;
+
+  while(co) {
+    /* only process this cookie if it is not expired or had no expire
+       date AND that if the cookie requires we're secure we must only
+       continue if we are! */
+    if( (co->expires<=0 || (co->expires> now)) &&
+        (co->secure?secure:TRUE) ) {
+
+      /* now check if the domain is correct */
+      if(!co->domain ||
+         (co->tailmatch && tailmatch(co->domain, host)) ||
+         (!co->tailmatch && strequal(host, co->domain)) ) {
+        /* the right part of the host matches the domain stuff in the
+           cookie data */
+
+        /* now check the left part of the path with the cookies path
+           requirement */
+        if(!co->path ||
+           /* not using checkprefix() because matching should be
+              case-sensitive */
+           !strncmp(co->path, path, strlen(co->path)) ) {
+
+          /* and now, we know this is a match and we should create an
+             entry for the return-linked-list */
+
+          newco = (struct Cookie *)malloc(sizeof(struct Cookie));
+          if(newco) {
+            /* first, copy the whole source cookie: */
+            memcpy(newco, co, sizeof(struct Cookie));
+
+            /* then modify our next */
+            newco->next = mainco;
+
+            /* point the main to us */
+            mainco = newco;
+          }
+          else {
+            /* failure, clear up the allocated chain and return NULL */
+            while(mainco) {
+              co = mainco->next;
+              free(mainco);
+              mainco = co;
+            }
+
+            return NULL;
+          }
+        }
+      }
+    }
+    co = co->next;
+  }
+
+  return mainco; /* return the new list */
 }
 
+/*****************************************************************************
+ *
+ * Curl_cookie_clearall()
+ *
+ * Clear all existing cookies and reset the counter.
+ *
+ ****************************************************************************/
+void Curl_cookie_clearall(struct CookieInfo *cookies)
+{
+  if(cookies) {
+    Curl_cookie_freelist(cookies->cookies);
+    cookies->cookies = NULL;
+    cookies->numcookies = 0;
+  }
+}
 
 /*****************************************************************************
  *
@@ -772,17 +823,56 @@ struct Cookie *Curl_cookie_getlist(struct CookieInfo *c,
 
 void Curl_cookie_freelist(struct Cookie *co)
 {
-   struct Cookie *next;
-   if(co) {
-      while(co) {
-         next = co->next;
-         free(co); /* we only free the struct since the "members" are all
+  struct Cookie *next;
+  if(co) {
+    while(co) {
+      next = co->next;
+      free(co); /* we only free the struct since the "members" are all
                       just copied! */
-         co = next;
-      }
-   }
+      co = next;
+    }
+  }
+}
+
+
+/*****************************************************************************
+ *
+ * Curl_cookie_clearsess()
+ *
+ * Free all session cookies in the cookies list.
+ *
+ ****************************************************************************/
+void Curl_cookie_clearsess(struct CookieInfo *cookies)
+{
+  struct Cookie *first, *curr, *next, *prev = NULL;
+
+  if(!cookies->cookies)
+    return;
+
+  first = curr = prev = cookies->cookies;
+
+  for(; curr; curr = next) {
+    next = curr->next;
+    if(!curr->expires) {
+      if(first == curr)
+        first = next;
+
+      if(prev == curr)
+        prev = next;
+      else
+        prev->next = next;
+
+      free(curr);
+      cookies->numcookies--;
+    }
+    else
+      prev = curr;
+  }
+
+  cookies->cookies = first;
 }
 
+
 /*****************************************************************************
  *
  * Curl_cookie_cleanup()
@@ -792,20 +882,48 @@ void Curl_cookie_freelist(struct Cookie *co)
  ****************************************************************************/
 void Curl_cookie_cleanup(struct CookieInfo *c)
 {
-   struct Cookie *co;
-   struct Cookie *next;
-   if(c) {
-      if(c->filename)
-         free(c->filename);
-      co = c->cookies;
-
-      while(co) {
-         next = co->next;
-         freecookie(co);
-         co = next;
-      }
-      free(c); /* free the base struct as well */
-   }
+  struct Cookie *co;
+  struct Cookie *next;
+  if(c) {
+    if(c->filename)
+      free(c->filename);
+    co = c->cookies;
+
+    while(co) {
+      next = co->next;
+      freecookie(co);
+      co = next;
+    }
+    free(c); /* free the base struct as well */
+  }
+}
+
+/* get_netscape_format()
+ *
+ * Formats a string for Netscape output file, w/o a newline at the end.
+ *
+ * Function returns a char * to a formatted line. Has to be free()d
+*/
+static char *get_netscape_format(const struct Cookie *co)
+{
+  return aprintf(
+    "%s%s\t" /* domain */
+    "%s\t"   /* tailmatch */
+    "%s\t"   /* path */
+    "%s\t"   /* secure */
+    "%" FORMAT_OFF_T "\t"   /* expires */
+    "%s\t"   /* name */
+    "%s",    /* value */
+    /* Make sure all domains are prefixed with a dot if they allow
+       tailmatching. This is Mozilla-style. */
+    (co->tailmatch && co->domain && co->domain[0] != '.')? ".":"",
+    co->domain?co->domain:"unknown",
+    co->tailmatch?"TRUE":"FALSE",
+    co->path?co->path:"/",
+    co->secure?"TRUE":"FALSE",
+    co->expires,
+    co->name,
+    co->value?co->value:"");
 }
 
 /*
@@ -839,33 +957,22 @@ int Curl_cookie_output(struct CookieInfo *c, char *dumphere)
   }
 
   if(c) {
+    char *format_ptr;
+
     fputs("# Netscape HTTP Cookie File\n"
-          "# http://www.netscape.com/newsref/std/cookie_spec.html\n"
+          "# http://curlm.haxx.se/rfc/cookie_spec.html\n"
           "# This file was generated by libcurl! Edit at your own risk.\n\n",
           out);
     co = c->cookies;
 
     while(co) {
-      fprintf(out,
-              "%s%s\t" /* domain */
-              "%s\t" /* tailmatch */
-              "%s\t" /* path */
-              "%s\t" /* secure */
-              "%u\t" /* expires */
-              "%s\t" /* name */
-              "%s\n", /* value */
-
-              /* Make sure all domains are prefixed with a dot if they allow
-                 tailmatching. This is Mozilla-style. */
-              (co->tailmatch && co->domain && co->domain[0] != '.')? ".":"",
-              co->domain?co->domain:"unknown",
-              co->tailmatch?"TRUE":"FALSE",
-              co->path?co->path:"/",
-              co->secure?"TRUE":"FALSE",
-              (unsigned int)co->expires,
-              co->name,
-              co->value?co->value:"");
-
+      format_ptr = get_netscape_format(co);
+      if (format_ptr == NULL) {
+        fprintf(out, "#\n# Fatal libcurl error\n");
+        return 1;
+      }
+      fprintf(out, "%s\n", format_ptr);
+      free(format_ptr);
       co=co->next;
     }
   }
@@ -876,4 +983,35 @@ int Curl_cookie_output(struct CookieInfo *c, char *dumphere)
   return 0;
 }
 
-#endif /* CURL_DISABLE_HTTP */
+struct curl_slist *Curl_cookie_list(struct SessionHandle *data)
+{
+  struct curl_slist *list = NULL;
+  struct curl_slist *beg;
+  struct Cookie *c;
+  char *line;
+
+  if ((data->cookies == NULL) ||
+      (data->cookies->numcookies == 0))
+    return NULL;
+
+  c = data->cookies->cookies;
+
+  beg = list;
+  while (c) {
+    /* fill the list with _all_ the cookies we know */
+    line = get_netscape_format(c);
+    if (line == NULL) {
+      /* get_netscape_format returns null only if we run out of memory */
+
+      curl_slist_free_all(beg); /* free some memory */
+      return NULL;
+    }
+    list = curl_slist_append(list, line);
+    free(line);
+    c = c->next;
+  }
+
+  return list;
+}
+
+#endif /* CURL_DISABLE_HTTP || CURL_DISABLE_COOKIES */