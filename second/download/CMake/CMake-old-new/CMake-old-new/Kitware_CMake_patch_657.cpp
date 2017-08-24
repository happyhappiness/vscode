@@ -1,16 +1,16 @@
 /***************************************************************************
- *                                  _   _ ____  _     
- *  Project                     ___| | | |  _ \| |    
- *                             / __| | | | |_) | |    
- *                            | (__| |_| |  _ <| |___ 
+ *                                  _   _ ____  _
+ *  Project                     ___| | | |  _ \| |
+ *                             / __| | | | |_) | |
+ *                            | (__| |_| |  _ <| |___
  *                             \___|\___/|_| \_\_____|
  *
- * Copyright (C) 1998 - 2002, Daniel Stenberg, <daniel@haxx.se>, et al.
+ * Copyright (C) 1998 - 2004, Daniel Stenberg, <daniel@haxx.se>, et al.
  *
  * This software is licensed as described in the file COPYING, which
  * you should have received as part of this distribution. The terms
  * are also available at http://curl.haxx.se/docs/copyright.html.
- * 
+ *
  * You may opt to use, copy, modify, merge, publish, distribute and/or sell
  * copies of the Software, and permit persons to whom the Software is
  * furnished to do so, under the terms of the COPYING file.
@@ -28,7 +28,7 @@ RECEIVING COOKIE INFORMATION
 ============================
 
 struct CookieInfo *cookie_init(char *file);
-        
+
         Inits a cookie struct to store data in a local file. This is always
         called before any cookies are set.
 
@@ -58,9 +58,9 @@ struct Cookies *cookie_getlist(struct CookieInfo *cookie,
 
         It shall only return cookies that haven't expired.
 
-    
+
 Example set of cookies:
-    
+
     Set-cookie: PRODUCTINFO=webxpress; domain=.fidelity.com; path=/; secure
     Set-cookie: PERSONALIZE=none;expires=Monday, 13-Jun-1988 03:04:55 GMT;
     domain=.fidelity.com; path=/ftgw; secure
@@ -77,6 +77,7 @@ Example set of cookies:
     13-Jun-1988 03:04:55 GMT; domain=.fidelity.com; path=/; secure
 ****/
 
+
 #include "setup.h"
 
 #ifndef CURL_DISABLE_HTTP
@@ -85,19 +86,23 @@ Example set of cookies:
 #include <string.h>
 #include <ctype.h>
 
+#include "urldata.h"
 #include "cookie.h"
 #include "getdate.h"
 #include "strequal.h"
 #include "strtok.h"
+#include "sendf.h"
+#include "memory.h"
 
 /* The last #include file should be: */
-#ifdef MALLOCDEBUG
+#ifdef CURLDEBUG
 #include "memdebug.h"
 #endif
 
-static void
-free_cookiemess(struct Cookie *co)
+static void freecookie(struct Cookie *co)
 {
+  if(co->expirestr)
+    free(co->expirestr);
   if(co->domain)
     free(co->domain);
   if(co->path)
@@ -110,6 +115,17 @@ free_cookiemess(struct Cookie *co)
   free(co);
 }
 
+static bool tailmatch(const char *little, const char *bigone)
+{
+  size_t littlelen = strlen(little);
+  size_t biglen = strlen(bigone);
+
+  if(littlelen > biglen)
+    return FALSE;
+
+  return (bool)strequal(little, bigone+biglen-littlelen);
+}
+
 /****************************************************************************
  *
  * Curl_cookie_add()
@@ -119,32 +135,45 @@ free_cookiemess(struct Cookie *co)
  ***************************************************************************/
 
 struct Cookie *
-Curl_cookie_add(struct CookieInfo *c,
+Curl_cookie_add(struct SessionHandle *data,
+                /* The 'data' pointer here may be NULL at times, and thus
+                   must only be used very carefully for things that can deal
+                   with data being NULL. Such as infof() and similar */
+
+                struct CookieInfo *c,
                 bool httpheader, /* TRUE if HTTP header-style line */
                 char *lineptr,   /* first character of the line */
-                char *domain)    /* default domain */
+                char *domain,    /* default domain */
+                char *path)      /* full path used when this cookie is set,
+                                    used to get default path for the cookie
+                                    unless set */
 {
   struct Cookie *clist;
-  char what[MAX_COOKIE_LINE];
+  char *what;
   char name[MAX_NAME];
   char *ptr;
   char *semiptr;
   struct Cookie *co;
   struct Cookie *lastc=NULL;
   time_t now = time(NULL);
   bool replace_old = FALSE;
+  bool badcookie = FALSE; /* cookies are good by default. mmmmm yummy */
 
   /* First, alloc and init a new struct for it */
-  co = (struct Cookie *)malloc(sizeof(struct Cookie));
+  co = (struct Cookie *)calloc(sizeof(struct Cookie), 1);
   if(!co)
     return NULL; /* bail out if we're this low on memory */
 
-  /* clear the whole struct first */
-  memset(co, 0, sizeof(struct Cookie));
-            
   if(httpheader) {
     /* This line was read off a HTTP-header */
     char *sep;
+
+    what = malloc(MAX_COOKIE_LINE);
+    if(!what) {
+      free(co);
+      return NULL;
+    }
+
     semiptr=strchr(lineptr, ';'); /* first, find a semicolon */
 
     while(*lineptr && isspace((int)*lineptr))
@@ -183,13 +212,82 @@ Curl_cookie_add(struct CookieInfo *c,
 
           if(strequal("path", name)) {
             co->path=strdup(whatptr);
+            if(!co->path) {
+              badcookie = TRUE; /* out of memory bad */
+              break;
+            }
           }
           else if(strequal("domain", name)) {
-            co->domain=strdup(whatptr);
-            co->field1= (char)((whatptr[0]=='.')?2:1);
+            /* note that this name may or may not have a preceeding dot, but
+               we don't care about that, we treat the names the same anyway */
+
+            const char *domptr=whatptr;
+            int dotcount=1;
+
+            /* Count the dots, we need to make sure that there are enough
+               of them. */
+
+            if('.' == whatptr[0])
+              /* don't count the initial dot, assume it */
+              domptr++;
+
+            do {
+              domptr = strchr(domptr, '.');
+              if(domptr) {
+                domptr++;
+                dotcount++;
+              }
+            } while(domptr);
+
+            /* The original Netscape cookie spec defined that this domain name
+               MUST have three dots (or two if one of the seven holy TLDs),
+               but it seems that these kinds of cookies are in use "out there"
+               so we cannot be that strict. I've therefore lowered the check
+               to not allow less than two dots. */
+
+            if(dotcount < 2) {
+              /* Received and skipped a cookie with a domain using too few
+                 dots. */
+              badcookie=TRUE; /* mark this as a bad cookie */
+              infof(data, "skipped cookie with illegal dotcount domain: %s\n",
+                    whatptr);
+            }
+            else {
+              /* Now, we make sure that our host is within the given domain,
+                 or the given domain is not valid and thus cannot be set. */
+
+              if('.' == whatptr[0])
+                whatptr++; /* ignore preceeding dot */
+
+              if(!domain || tailmatch(whatptr, domain)) {
+                const char *tailptr=whatptr;
+                if(tailptr[0] == '.')
+                  tailptr++;
+                co->domain=strdup(tailptr); /* don't prefix w/dots
+                                               internally */
+                if(!co->domain) {
+                  badcookie = TRUE;
+                  break;
+                }
+                co->tailmatch=TRUE; /* we always do that if the domain name was
+                                       given */
+              }
+              else {
+                /* we did not get a tailmatch and then the attempted set domain
+                   is not a domain to which the current host belongs. Mark as
+                   bad. */
+                badcookie=TRUE;
+                infof(data, "skipped cookie with bad tailmatch domain: %s\n",
+                      whatptr);
+              }
+            }
           }
           else if(strequal("version", name)) {
             co->version=strdup(whatptr);
+            if(!co->version) {
+              badcookie = TRUE;
+              break;
+            }
           }
           else if(strequal("max-age", name)) {
             /* Defined in RFC2109:
@@ -202,16 +300,28 @@ Curl_cookie_add(struct CookieInfo *c,
 
              */
             co->maxage = strdup(whatptr);
+            if(!co->maxage) {
+              badcookie = TRUE;
+              break;
+            }
             co->expires =
-              atoi((*co->maxage=='\"')?&co->maxage[1]:&co->maxage[0]) + (long)now;
+              atoi((*co->maxage=='\"')?&co->maxage[1]:&co->maxage[0]) + now;
           }
           else if(strequal("expires", name)) {
             co->expirestr=strdup(whatptr);
-            co->expires = (long)curl_getdate(what, &now);
+            if(!co->expirestr) {
+              badcookie = TRUE;
+              break;
+            }
+            co->expires = curl_getdate(what, &now);
           }
           else if(!co->name) {
             co->name = strdup(name);
             co->value = strdup(whatptr);
+            if(!co->name || !co->value) {
+              badcookie = TRUE;
+              break;
+            }
           }
           /*
             else this is the second (or more) name we don't know
@@ -248,23 +358,39 @@ Curl_cookie_add(struct CookieInfo *c,
         semiptr=strchr(ptr, '\0');
     } while(semiptr);
 
-    if(NULL == co->name) {
-      /* we didn't get a cookie name, this is an illegal line, bail out */
-      if(co->domain)
-        free(co->domain);
-      if(co->path)
-        free(co->path);
-      if(co->name)
-        free(co->name);
-      if(co->value)
-        free(co->value);
-      free(co);
+    if(!badcookie && !co->domain) {
+      if(domain) {
+        /* no domain was given in the header line, set the default */
+        co->domain=strdup(domain);
+        if(!co->domain)
+          badcookie = TRUE;
+      }
+    }
+
+    if(!badcookie && !co->path && path) {
+      /* no path was given in the header line, set the default  */
+      char *endslash = strrchr(path, '/');
+      if(endslash) {
+        size_t pathlen = endslash-path+1; /* include the ending slash */
+        co->path=malloc(pathlen+1); /* one extra for the zero byte */
+        if(co->path) {
+          memcpy(co->path, path, pathlen);
+          co->path[pathlen]=0; /* zero terminate */
+        }
+        else
+          badcookie = TRUE;
+      }
+    }
+
+    free(what);
+
+    if(badcookie || !co->name) {
+      /* we didn't get a cookie name or a bad one,
+         this is an illegal line, bail out */
+      freecookie(co);
       return NULL;
     }
 
-    if(NULL == co->domain)
-      /* no domain given in the header line, set the default now */
-      co->domain=domain?strdup(domain):NULL;
   }
   else {
     /* This line is NOT a HTTP header style line, we do offer support for
@@ -286,7 +412,7 @@ Curl_cookie_add(struct CookieInfo *c,
     if(ptr)
       *ptr=0; /* clear it */
 
-    firstptr=strtok_r(lineptr, "\t", &tok_buf); /* first tokenize it on the TAB */
+    firstptr=strtok_r(lineptr, "\t", &tok_buf); /* tokenize it on the TAB */
 
     /* Here's a quick check to eliminate normal HTTP-headers from this */
     if(!firstptr || strchr(firstptr, ':')) {
@@ -296,10 +422,15 @@ Curl_cookie_add(struct CookieInfo *c,
 
     /* Now loop through the fields and init the struct we already have
        allocated */
-    for(ptr=firstptr, fields=0; ptr; ptr=strtok_r(NULL, "\t", &tok_buf), fields++) {
+    for(ptr=firstptr, fields=0; ptr && !badcookie;
+        ptr=strtok_r(NULL, "\t", &tok_buf), fields++) {
       switch(fields) {
       case 0:
+        if(ptr[0]=='.') /* skip preceeding dots */
+          ptr++;
         co->domain = strdup(ptr);
+        if(!co->domain)
+          badcookie = TRUE;
         break;
       case 1:
         /* This field got its explanation on the 23rd of May 2001 by
@@ -311,10 +442,8 @@ Curl_cookie_add(struct CookieInfo *c,
 
            As far as I can see, it is set to true when the cookie says
            .domain.com and to false when the domain is complete www.domain.com
-
-           We don't currently take advantage of this knowledge.
         */
-        co->field1=(char)(strequal(ptr, "TRUE")+1); /* store information */
+        co->tailmatch=(bool)strequal(ptr, "TRUE"); /* store information */
         break;
       case 2:
         /* It turns out, that sometimes the file format allows the path
@@ -323,10 +452,14 @@ Curl_cookie_add(struct CookieInfo *c,
         if (strcmp("TRUE", ptr) && strcmp("FALSE", ptr)) {
           /* only if the path doesn't look like a boolean option! */
           co->path = strdup(ptr);
+          if(!co->path)
+            badcookie = TRUE;
           break;
         }
         /* this doesn't look like a path, make one up! */
         co->path = strdup("/");
+        if(!co->path)
+          badcookie = TRUE;
         fields++; /* add a field and fall down to secure */
         /* FALLTHROUGH */
       case 3:
@@ -337,17 +470,31 @@ Curl_cookie_add(struct CookieInfo *c,
         break;
       case 5:
         co->name = strdup(ptr);
+        if(!co->name)
+          badcookie = TRUE;
         break;
       case 6:
         co->value = strdup(ptr);
+        if(!co->value)
+          badcookie = TRUE;
         break;
       }
     }
+    if(6 == fields) {
+      /* we got a cookie with blank contents, fix it */
+      co->value = strdup("");
+      if(!co->value)
+        badcookie = TRUE;
+      else
+        fields++;
+    }
 
-    if(7 != fields) {
-      /* we did not find the sufficient number of fields to recognize this
-         as a valid line, abort and go home */
-      free_cookiemess(co);
+    if(!badcookie && (7 != fields))
+      /* we did not find the sufficient number of fields */
+      badcookie = TRUE;
+
+    if(badcookie) {
+      freecookie(co);
       return NULL;
     }
 
@@ -356,7 +503,7 @@ Curl_cookie_add(struct CookieInfo *c,
   if(!c->running &&    /* read from a file */
      c->newsession &&  /* clean session cookies */
      !co->expires) {   /* this is a session cookie since it doesn't expire! */
-    free_cookiemess(co);
+    freecookie(co);
     return NULL;
   }
 
@@ -373,13 +520,8 @@ Curl_cookie_add(struct CookieInfo *c,
       /* the names are identical */
 
       if(clist->domain && co->domain) {
-        if(strequal(clist->domain, co->domain) ||
-           (clist->domain[0]=='.' &&
-            strequal(&(clist->domain[1]), co->domain)) ||
-           (co->domain[0]=='.' &&
-            strequal(clist->domain, &(co->domain[1]))) )
-          /* The domains are identical, or at least identical if you skip the
-             preceeding dot */
+        if(strequal(clist->domain, co->domain))
+          /* The domains are identical */
           replace_old=TRUE;
       }
       else if(!clist->domain && !co->domain)
@@ -399,7 +541,7 @@ Curl_cookie_add(struct CookieInfo *c,
           replace_old = TRUE;
         else
           replace_old = FALSE;
-        
+
       }
 
       if(replace_old && !co->livecookie && clist->livecookie) {
@@ -409,16 +551,7 @@ Curl_cookie_add(struct CookieInfo *c,
            live cookies stay alive */
 
         /* Free the newcomer and get out of here! */
-        if(co->domain)
-          free(co->domain);
-        if(co->path)
-          free(co->path);
-        if(co->name)
-          free(co->name);
-        if(co->value)
-          free(co->value);
-
-        free(co);
+        freecookie(co);
         return NULL;
       }
 
@@ -460,6 +593,12 @@ Curl_cookie_add(struct CookieInfo *c,
     clist = clist->next;
   }
 
+  if(c->running)
+    /* Only show this when NOT reading the cookies from a file */
+    infof(data, "%s cookie %s=\"%s\" for domain %s, path %s, expire %d\n",
+          replace_old?"Replaced":"Added", co->name, co->value,
+          co->domain, co->path, co->expires);
+
   if(!replace_old) {
     /* then make the last item point on this new one */
     if(lastc)
@@ -469,7 +608,6 @@ Curl_cookie_add(struct CookieInfo *c,
   }
 
   c->numcookies++; /* one more cookie in the jar */
-
   return co;
 }
 
@@ -483,21 +621,20 @@ Curl_cookie_add(struct CookieInfo *c,
  * If 'newsession' is TRUE, discard all "session cookies" on read from file.
  *
  ****************************************************************************/
-struct CookieInfo *Curl_cookie_init(char *file,
+struct CookieInfo *Curl_cookie_init(struct SessionHandle *data,
+                                    char *file,
                                     struct CookieInfo *inc,
                                     bool newsession)
 {
-  char line[MAX_COOKIE_LINE];
   struct CookieInfo *c;
   FILE *fp;
   bool fromfile=TRUE;
-  
+
   if(NULL == inc) {
     /* we didn't get a struct, create one */
-    c = (struct CookieInfo *)malloc(sizeof(struct CookieInfo));
+    c = (struct CookieInfo *)calloc(1, sizeof(struct CookieInfo));
     if(!c)
       return NULL; /* failed to get memory */
-    memset(c, 0, sizeof(struct CookieInfo));
     c->filename = strdup(file?file:"none"); /* copy the name just in case */
   }
   else {
@@ -518,20 +655,25 @@ struct CookieInfo *Curl_cookie_init(char *file,
   if(fp) {
     char *lineptr;
     bool headerline;
-    while(fgets(line, MAX_COOKIE_LINE, fp)) {
-      if(checkprefix("Set-Cookie:", line)) {
-        /* This is a cookie line, get it! */
-        lineptr=&line[11];
-        headerline=TRUE;
-      }
-      else {
-        lineptr=line;
-        headerline=FALSE;
-      }
-      while(*lineptr && isspace((int)*lineptr))
-        lineptr++;
 
-      Curl_cookie_add(c, headerline, lineptr, NULL);
+    char *line = (char *)malloc(MAX_COOKIE_LINE);
+    if(line) {
+      while(fgets(line, MAX_COOKIE_LINE, fp)) {
+        if(checkprefix("Set-Cookie:", line)) {
+          /* This is a cookie line, get it! */
+          lineptr=&line[11];
+          headerline=TRUE;
+        }
+        else {
+          lineptr=line;
+          headerline=FALSE;
+        }
+        while(*lineptr && isspace((int)*lineptr))
+          lineptr++;
+
+        Curl_cookie_add(data, c, headerline, lineptr, NULL, NULL);
+      }
+      free(line); /* free the line buffer */
     }
     if(fromfile)
       fclose(fp);
@@ -560,9 +702,6 @@ struct Cookie *Curl_cookie_getlist(struct CookieInfo *c,
    struct Cookie *newco;
    struct Cookie *co;
    time_t now = time(NULL);
-   int hostlen=(int)strlen(host);
-   int domlen;
-
    struct Cookie *mainco=NULL;
 
    if(!c || !c->cookies)
@@ -571,43 +710,52 @@ struct Cookie *Curl_cookie_getlist(struct CookieInfo *c,
    co = c->cookies;
 
    while(co) {
-      /* only process this cookie if it is not expired or had no expire
-         date AND that if the cookie requires we're secure we must only
-         continue if we are! */
+     /* only process this cookie if it is not expired or had no expire
+        date AND that if the cookie requires we're secure we must only
+        continue if we are! */
      if( (co->expires<=0 || (co->expires> now)) &&
          (co->secure?secure:TRUE) ) {
 
-         /* now check if the domain is correct */
-         domlen=co->domain?(int)strlen(co->domain):0;
-         if(!co->domain ||
-            ((domlen<=hostlen) &&
-             strequal(host+(hostlen-domlen), co->domain)) ) {
-            /* the right part of the host matches the domain stuff in the
-               cookie data */
-
-            /* now check the left part of the path with the cookies path
-               requirement */
-           if(!co->path ||
-              checkprefix(co->path, path) ) {
-
-               /* and now, we know this is a match and we should create an
-                  entry for the return-linked-list */
-
-               newco = (struct Cookie *)malloc(sizeof(struct Cookie));
-               if(newco) {
-                  /* first, copy the whole source cookie: */
-                  memcpy(newco, co, sizeof(struct Cookie));
-
-                  /* then modify our next */
-                  newco->next = mainco;
-
-                  /* point the main to us */
-                  mainco = newco;
-               }
-            }
+       /* now check if the domain is correct */
+       if(!co->domain ||
+          (co->tailmatch && tailmatch(co->domain, host)) ||
+          (!co->tailmatch && strequal(host, co->domain)) ) {
+         /* the right part of the host matches the domain stuff in the
+            cookie data */
+
+         /* now check the left part of the path with the cookies path
+            requirement */
+         if(!co->path ||
+            checkprefix(co->path, path) ) {
+
+           /* and now, we know this is a match and we should create an
+              entry for the return-linked-list */
+
+           newco = (struct Cookie *)malloc(sizeof(struct Cookie));
+           if(newco) {
+             /* first, copy the whole source cookie: */
+             memcpy(newco, co, sizeof(struct Cookie));
+
+             /* then modify our next */
+             newco->next = mainco;
+
+             /* point the main to us */
+             mainco = newco;
+           }
+           else {
+              /* failure, clear up the allocated chain and return NULL */
+             while(mainco) {
+               co = mainco->next;
+               free(mainco);
+               mainco = co;
+             }
+
+             return NULL;
+           }
          }
-      }
-      co = co->next;
+       }
+     }
+     co = co->next;
    }
 
    return mainco; /* return the new list */
@@ -652,24 +800,8 @@ void Curl_cookie_cleanup(struct CookieInfo *c)
       co = c->cookies;
 
       while(co) {
-         if(co->name)
-            free(co->name);
-         if(co->value)
-            free(co->value);
-         if(co->domain)
-            free(co->domain);
-         if(co->path)
-            free(co->path);
-         if(co->expirestr)
-            free(co->expirestr);
-
-         if(co->version)
-            free(co->version);
-         if(co->maxage)
-            free(co->maxage);
-
          next = co->next;
-         free(co);
+         freecookie(co);
          co = next;
       }
       free(c); /* free the base struct as well */
@@ -712,18 +844,22 @@ int Curl_cookie_output(struct CookieInfo *c, char *dumphere)
           "# This file was generated by libcurl! Edit at your own risk.\n\n",
           out);
     co = c->cookies;
-     
+
     while(co) {
       fprintf(out,
-              "%s\t" /* domain */
-              "%s\t" /* field1 */
+              "%s%s\t" /* domain */
+              "%s\t" /* tailmatch */
               "%s\t" /* path */
               "%s\t" /* secure */
               "%u\t" /* expires */
               "%s\t" /* name */
               "%s\n", /* value */
+
+              /* Make sure all domains are prefixed with a dot if they allow
+                 tailmatching. This is Mozilla-style. */
+              (co->tailmatch && co->domain && co->domain[0] != '.')? ".":"",
               co->domain?co->domain:"unknown",
-              co->field1==2?"TRUE":"FALSE",
+              co->tailmatch?"TRUE":"FALSE",
               co->path?co->path:"/",
               co->secure?"TRUE":"FALSE",
               (unsigned int)co->expires,
@@ -740,39 +876,4 @@ int Curl_cookie_output(struct CookieInfo *c, char *dumphere)
   return 0;
 }
 
-#ifdef CURL_COOKIE_DEBUG
-
-/*
- * On my Solaris box, this command line builds this test program:
- *
- * gcc -g -o cooktest -DCURL_COOKIE_DEBUG -DHAVE_CONFIG_H -I.. -I../include cookie.c strequal.o getdate.o memdebug.o mprintf.o strtok.o -lnsl -lsocket
- *
- */
-
-int main(int argc, char **argv)
-{
-  struct CookieInfo *c=NULL;
-  if(argc>1) {
-    c = Curl_cookie_init(argv[1], c);
-    Curl_cookie_add(c, TRUE, "PERSONALIZE=none;expires=Monday, 13-Jun-1988 03:04:55 GMT; domain=.fidelity.com; path=/ftgw; secure");
-    Curl_cookie_add(c, TRUE, "foobar=yes; domain=.haxx.se; path=/looser;");
-    c = Curl_cookie_init(argv[1], c);
-
-    Curl_cookie_output(c);
-    Curl_cookie_cleanup(c);
-    return 0;
-  }
-  return 1;
-}
-
-#endif
-
 #endif /* CURL_DISABLE_HTTP */
-
-/*
- * local variables:
- * eval: (load-file "../curl-mode.el")
- * end:
- * vim600: fdm=marker
- * vim: et sw=2 ts=2 sts=2 tw=78
- */