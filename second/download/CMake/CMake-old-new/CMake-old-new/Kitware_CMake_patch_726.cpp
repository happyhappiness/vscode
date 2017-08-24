@@ -1,5 +1,5 @@
 /* ============================================================================
- * Copyright (C) 1998 Angus Mackay. All rights reserved; 
+ * Copyright (C) 1998 - 2002, Daniel Stenberg, <daniel@haxx.se>, et al.
  *
  * Redistribution and use are freely permitted provided that:
  *
@@ -93,14 +93,10 @@ char *getpass_r(const char *prompt, char *buffer, size_t buflen)
 #include "memdebug.h"
 #endif
 
-/* no perror? make an fprintf! */
-#ifndef HAVE_PERROR
-#  define perror(x) fprintf(stderr, "Error in: %s\n", x)
-#endif
-
 char *getpass_r(const char *prompt, char *buffer, size_t buflen)
 {
   FILE *infp;
+  char infp_fclose = 0;
   FILE *outfp;
   RETSIGTYPE (*sigint)();
 #ifndef __EMX__
@@ -127,41 +123,30 @@ char *getpass_r(const char *prompt, char *buffer, size_t buflen)
   sigtstp = signal(SIGTSTP, SIG_IGN);
 #endif
 
-  if( (infp=fopen("/dev/tty", "r")) == NULL )
-  {
+  infp=fopen("/dev/tty", "r");
+  if( NULL == infp )
     infp = stdin;
-  }
-  if( (outfp=fopen("/dev/tty", "w")) == NULL )
-  {
-    outfp = stderr;
-  }
+  else
+    infp_fclose = 1;
+
+  outfp = stderr;
+
   infd = fileno(infp);
   outfd = fileno(outfp);
 
   /* dissable echo */
 #ifdef HAVE_TERMIOS_H
-  if(tcgetattr(outfd, &orig) != 0)
-  {
-    ; /*perror("tcgetattr");*/
-  }
+  tcgetattr(outfd, &orig);
+
   noecho = orig;
   noecho.c_lflag &= ~ECHO;
-  if(tcsetattr(outfd, TCSANOW, &noecho) != 0)
-  {
-    ; /*perror("tcgetattr");*/
-  }
+  tcsetattr(outfd, TCSANOW, &noecho);
 #else
 #  ifdef HAVE_TERMIO_H
-  if(ioctl(outfd, TCGETA, &orig) != 0)
-  {
-    ; /*perror("ioctl");*/
-  }
+  ioctl(outfd, TCGETA, &orig);
   noecho = orig;
   noecho.c_lflag &= ~ECHO;
-  if(ioctl(outfd, TCSETA, &noecho) != 0)
-  {
-    ; /*perror("ioctl");*/
-  }
+  ioctl(outfd, TCSETA, &noecho);
 #  else
 #  endif
 #endif
@@ -187,16 +172,10 @@ char *getpass_r(const char *prompt, char *buffer, size_t buflen)
    * user types more than buflen
    */
 #ifdef HAVE_TERMIOS_H
-  if(tcsetattr(outfd, TCSAFLUSH, &orig) != 0)
-  {
-    ; /*perror("tcgetattr");*/
-  }
+  tcsetattr(outfd, TCSAFLUSH, &orig);
 #else
 #  ifdef HAVE_TERMIO_H
-  if(ioctl(outfd, TCSETA, &orig) != 0)
-  {
-    ; /*perror("ioctl");*/
-  }
+  ioctl(outfd, TCSETA, &orig);
 #  else
 #  endif
 #endif
@@ -206,6 +185,9 @@ char *getpass_r(const char *prompt, char *buffer, size_t buflen)
   signal(SIGTSTP, sigtstp);
 #endif
 
+  if(infp_fclose)
+    fclose(infp);
+
   return buffer; /* we always return success */
 }
 #endif /* VMS */