   /* 20000318 mgs
    * this is needed by the emx system, SIGTSTP is not a supported signal */
 #ifndef __EMX__
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
 
   fputs(prompt, outfp);
   fflush(outfp);
