@@ -6,7 +6,7 @@
  *                            | (__| |_| |  _ <| |___
  *                             \___|\___/|_| \_\_____|
  *
- * Copyright (C) 1998 - 2004, Daniel Stenberg, <daniel@haxx.se>, et al.
+ * Copyright (C) 1998 - 2005, Daniel Stenberg, <daniel@haxx.se>, et al.
  *
  * This software is licensed as described in the file COPYING, which
  * you should have received as part of this distribution. The terms
@@ -42,7 +42,7 @@
 #endif
 
 #define MEMDEBUG_NODEFINES /* don't redefine the standard functions */
-#include "curl_memory.h"
+#include "memory.h"
 #include "memdebug.h"
 
 struct memdebug {
@@ -61,25 +61,29 @@ struct memdebug {
  */
 
 #define logfile curl_debuglogfile
-FILE *curl_debuglogfile;
-static bool memlimit; /* enable memory limit */
-static long memsize;  /* set number of mallocs allowed */
+FILE *curl_debuglogfile = NULL;
+static bool memlimit = FALSE; /* enable memory limit */
+static long memsize = 0;  /* set number of mallocs allowed */
 
 /* this sets the log file name */
 void curl_memdebug(const char *logname)
 {
-  if(logname)
-    logfile = fopen(logname, "w");
-  else
-    logfile = stderr;
+  if (!logfile) {
+    if(logname)
+      logfile = fopen(logname, "w");
+    else
+      logfile = stderr;
+  }
 }
 
 /* This function sets the number of malloc() calls that should return
    successfully! */
 void curl_memlimit(long limit)
 {
-  memlimit = TRUE;
-  memsize = limit;
+  if (!memlimit) {
+    memlimit = TRUE;
+    memsize = limit;
+  }
 }
 
 /* returns TRUE if this isn't allowed! */
@@ -95,6 +99,7 @@ static bool countcheck(const char *func, int line, const char *source)
       if(source)
         fprintf(stderr, "LIMIT %s:%d %s reached memlimit\n",
                 source, line, func);
+      errno = ENOMEM;
       return TRUE; /* RETURN ERROR! */
     }
     else
@@ -200,7 +205,7 @@ void *curl_dorealloc(void *ptr, size_t wantedsize,
 
   mem=(struct memdebug *)(Curl_crealloc)(mem, size);
   if(logfile)
-    fprintf(logfile, "MEM %s:%d realloc(0x%x, %zd) = %p\n",
+    fprintf(logfile, "MEM %s:%d realloc(%p, %zd) = %p\n",
             source, line, ptr, wantedsize, mem?mem->mem:NULL);
 
   if(mem) {