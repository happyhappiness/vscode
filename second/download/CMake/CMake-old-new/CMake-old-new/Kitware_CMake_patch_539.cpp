@@ -5,7 +5,7 @@
  *                            | (__| |_| |  _ <| |___
  *                             \___|\___/|_| \_\_____|
  *
- * Copyright (C) 1998 - 2004, Daniel Stenberg, <daniel@haxx.se>, et al.
+ * Copyright (C) 1998 - 2007, Daniel Stenberg, <daniel@haxx.se>, et al.
  *
  * This software is licensed as described in the file COPYING, which
  * you should have received as part of this distribution. The terms
@@ -30,12 +30,14 @@
 #include <stdarg.h>
 #include <stdlib.h>
 #include <ctype.h>
+#ifdef HAVE_SYS_TYPES_H
 #include <sys/types.h>
+#endif
+#ifdef HAVE_SYS_STAT_H
 #include <sys/stat.h>
+#endif
 
-#include <errno.h>
-
-#if defined(WIN32) && !defined(__GNUC__) || defined(__MINGW32__)
+#ifdef WIN32
 #include <time.h>
 #include <io.h>
 #include <fcntl.h>
@@ -46,7 +48,9 @@
 #ifdef HAVE_NETINET_IN_H
 #include <netinet/in.h>
 #endif
+#ifdef HAVE_SYS_TIME_H
 #include <sys/time.h>
+#endif
 #ifdef HAVE_UNISTD_H
 #include <unistd.h>
 #endif
@@ -66,9 +70,6 @@
 #include <sys/param.h>
 #endif
 
-#ifdef HAVE_SYS_STAT_H
-#include <sys/stat.h>
-#endif
 #ifdef HAVE_FCNTL_H
 #include <fcntl.h>
 #endif
@@ -85,7 +86,8 @@
 #include "getinfo.h"
 #include "transfer.h"
 #include "url.h"
-#include "curl_memory.h"
+#include "memory.h"
+#include "parsedate.h" /* for the week day and month names */
 
 #define _MPRINTF_REPLACE /* use our functions only */
 #include <curl/mprintf.h>
@@ -100,10 +102,10 @@
  */
 CURLcode Curl_file_connect(struct connectdata *conn)
 {
-  char *real_path = curl_unescape(conn->path, 0);
+  char *real_path = curl_easy_unescape(conn->data, conn->data->reqdata.path, 0, NULL);
   struct FILEPROTO *file;
   int fd;
-#if defined(WIN32) || defined(__EMX__)
+#if defined(WIN32) || defined(MSDOS) || defined(__EMX__)
   int i;
   char *actual_path;
 #endif
@@ -117,9 +119,13 @@ CURLcode Curl_file_connect(struct connectdata *conn)
     return CURLE_OUT_OF_MEMORY;
   }
 
-  conn->proto.file = file;
+  if (conn->data->reqdata.proto.file) {
+    free(conn->data->reqdata.proto.file);
+  }
+
+  conn->data->reqdata.proto.file = file;
 
-#if defined(WIN32) || defined(__EMX__)
+#if defined(WIN32) || defined(MSDOS) || defined(__EMX__)
   /* If the first character is a slash, and there's
      something that looks like a drive at the beginning of
      the path, skip the slash.  If we remove the initial
@@ -143,7 +149,7 @@ CURLcode Curl_file_connect(struct connectdata *conn)
     actual_path++;
   }
 
-  /* change path separators from '/' to '\\' for Windows and OS/2 */
+  /* change path separators from '/' to '\\' for DOS, Windows and OS/2 */
   for (i=0; actual_path[i] != '\0'; ++i)
     if (actual_path[i] == '/')
       actual_path[i] = '\\';
@@ -156,39 +162,39 @@ CURLcode Curl_file_connect(struct connectdata *conn)
 #endif
   file->freepath = real_path; /* free this when done */
 
+  file->fd = fd;
   if(!conn->data->set.upload && (fd == -1)) {
-    failf(conn->data, "Couldn't open file %s", conn->path);
-    Curl_file_done(conn, CURLE_FILE_COULDNT_READ_FILE);
+    failf(conn->data, "Couldn't open file %s", conn->data->reqdata.path);
+    Curl_file_done(conn, CURLE_FILE_COULDNT_READ_FILE, FALSE);
     return CURLE_FILE_COULDNT_READ_FILE;
   }
-  file->fd = fd;
 
   return CURLE_OK;
 }
 
-#if defined(WIN32) && (SIZEOF_CURL_OFF_T > 4)
-#define lseek(x,y,z) _lseeki64(x, y, z)
-#endif
-
 CURLcode Curl_file_done(struct connectdata *conn,
-                        CURLcode status)
+                        CURLcode status, bool premature)
 {
-  struct FILEPROTO *file = conn->proto.file;
+  struct FILEPROTO *file = conn->data->reqdata.proto.file;
   (void)status; /* not used */
+  (void)premature; /* not used */
   Curl_safefree(file->freepath);
 
+  if(file->fd != -1)
+    close(file->fd);
+
   return CURLE_OK;
 }
 
-#if defined(WIN32) || defined(__EMX__)
+#if defined(WIN32) || defined(MSDOS) || defined(__EMX__)
 #define DIRSEP '\\'
 #else
 #define DIRSEP '/'
 #endif
 
 static CURLcode file_upload(struct connectdata *conn)
 {
-  struct FILEPROTO *file = conn->proto.file;
+  struct FILEPROTO *file = conn->data->reqdata.proto.file;
   char *dir = strchr(file->path, DIRSEP);
   FILE *fp;
   CURLcode res=CURLE_OK;
@@ -205,7 +211,7 @@ static CURLcode file_upload(struct connectdata *conn)
    */
   conn->fread = data->set.fread;
   conn->fread_in = data->set.in;
-  conn->upload_fromhere = buf;
+  conn->data->reqdata.upload_fromhere = buf;
 
   if(!dir)
     return CURLE_FILE_COULDNT_READ_FILE; /* fix: better error code */
@@ -227,13 +233,13 @@ static CURLcode file_upload(struct connectdata *conn)
     int readcount;
     res = Curl_fillreadbuffer(conn, BUFSIZE, &readcount);
     if(res)
-      return res;
-
-    nread = (size_t)readcount;
+      break;
 
-    if (nread <= 0)
+    if (readcount <= 0)  /* fix questionable compare error. curlvms */
       break;
 
+    nread = (size_t)readcount;
+
     /* write the data to the target */
     nwrite = fwrite(buf, 1, nread, fp);
     if(nwrite != nread) {
@@ -266,15 +272,17 @@ static CURLcode file_upload(struct connectdata *conn)
  * opposed to sockets) we instead perform the whole do-operation in this
  * function.
  */
-CURLcode Curl_file(struct connectdata *conn)
+CURLcode Curl_file(struct connectdata *conn, bool *done)
 {
   /* This implementation ignores the host name in conformance with
      RFC 1738. Only local files (reachable via the standard file system)
      are supported. This means that files on remotely mounted directories
      (via NFS, Samba, NT sharing) can be accessed through a file:// URL
   */
   CURLcode res = CURLE_OK;
-  struct stat statbuf;
+  struct_stat statbuf; /* struct_stat instead of struct stat just to allow the
+                          Windows version to have a different struct without
+                          having to redefine the simple word 'stat' */
   curl_off_t expected_size=0;
   bool fstated=FALSE;
   ssize_t nread;
@@ -284,6 +292,8 @@ CURLcode Curl_file(struct connectdata *conn)
   int fd;
   struct timeval now = Curl_tvnow();
 
+  *done = TRUE; /* unconditionally */
+
   Curl_readwrite_init(conn);
   Curl_initinfo(data);
   Curl_pgrsStartNow(data);
@@ -292,7 +302,7 @@ CURLcode Curl_file(struct connectdata *conn)
     return file_upload(conn);
 
   /* get the fd from the connection phase */
-  fd = conn->proto.file->fd;
+  fd = conn->data->reqdata.proto.file->fd;
 
   /* VMS: This only works reliable for STREAMLF files */
   if( -1 != fstat(fd, &statbuf)) {
@@ -308,40 +318,45 @@ CURLcode Curl_file(struct connectdata *conn)
     CURLcode result;
     snprintf(buf, sizeof(data->state.buffer),
              "Content-Length: %" FORMAT_OFF_T "\r\n", expected_size);
-    result = Curl_client_write(data, CLIENTWRITE_BOTH, buf, 0);
+    result = Curl_client_write(conn, CLIENTWRITE_BOTH, buf, 0);
     if(result)
       return result;
 
-    result = Curl_client_write(data, CLIENTWRITE_BOTH,
+    result = Curl_client_write(conn, CLIENTWRITE_BOTH,
                                (char *)"Accept-ranges: bytes\r\n", 0);
     if(result)
       return result;
 
-#ifdef HAVE_STRFTIME
     if(fstated) {
       struct tm *tm;
-      time_t cuClock = (time_t)statbuf.st_mtime;
+      time_t clock = (time_t)statbuf.st_mtime;
 #ifdef HAVE_GMTIME_R
       struct tm buffer;
-      tm = (struct tm *)gmtime_r(&cuClock, &buffer);
+      tm = (struct tm *)gmtime_r(&clock, &buffer);
 #else
-      tm = gmtime(&cuClock);
+      tm = gmtime(&clock);
 #endif
       /* format: "Tue, 15 Nov 1994 12:45:26 GMT" */
-      strftime(buf, BUFSIZE-1, "Last-Modified: %a, %d %b %Y %H:%M:%S GMT\r\n",
-               tm);
-      result = Curl_client_write(data, CLIENTWRITE_BOTH, buf, 0);
+      snprintf(buf, BUFSIZE-1,
+               "Last-Modified: %s, %02d %s %4d %02d:%02d:%02d GMT\r\n",
+               Curl_wkday[tm->tm_wday?tm->tm_wday-1:6],
+               tm->tm_mday,
+               Curl_month[tm->tm_mon],
+               tm->tm_year + 1900,
+               tm->tm_hour,
+               tm->tm_min,
+               tm->tm_sec);
+      result = Curl_client_write(conn, CLIENTWRITE_BOTH, buf, 0);
     }
-#endif
     return result;
   }
 
-  /* Added by Dolbneff A.V & Spiridonoff A.V */
-  if (conn->resume_from <= expected_size)
-    expected_size -= conn->resume_from;
-  else
-    /* Is this error code suitable in such situation? */
-    return CURLE_FTP_BAD_DOWNLOAD_RESUME;
+  if (data->reqdata.resume_from <= expected_size)
+    expected_size -= data->reqdata.resume_from;
+  else {
+    failf(data, "failed to resume file:// transfer");
+    return CURLE_BAD_DOWNLOAD_RESUME;
+  }
 
   if (fstated && (expected_size == 0))
     return CURLE_OK;
@@ -353,8 +368,11 @@ CURLcode Curl_file(struct connectdata *conn)
   if(fstated)
     Curl_pgrsSetDownloadSize(data, expected_size);
 
-  if(conn->resume_from)
-    lseek(fd, conn->resume_from, SEEK_SET);
+  if(data->reqdata.resume_from) {
+    if(data->reqdata.resume_from !=
+       lseek(fd, data->reqdata.resume_from, SEEK_SET))
+      return CURLE_BAD_DOWNLOAD_RESUME;
+  }
 
   Curl_pgrsTime(data, TIMER_STARTTRANSFER);
 
@@ -369,7 +387,7 @@ CURLcode Curl_file(struct connectdata *conn)
 
     bytecount += nread;
 
-    res = Curl_client_write(data, CLIENTWRITE_BODY, buf, nread);
+    res = Curl_client_write(conn, CLIENTWRITE_BODY, buf, nread);
     if(res)
       return res;
 
@@ -383,8 +401,7 @@ CURLcode Curl_file(struct connectdata *conn)
   if(Curl_pgrsUpdate(conn))
     res = CURLE_ABORTED_BY_CALLBACK;
 
-  close(fd);
-
   return res;
 }
+
 #endif