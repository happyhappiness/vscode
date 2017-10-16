   outfd = fileno(outfp);
 
   /* dissable echo */
 #ifdef HAVE_TERMIOS_H
   if(tcgetattr(outfd, &orig) != 0)
   {
-    perror("tcgetattr");
+    ; /*perror("tcgetattr");*/
   }
   noecho = orig;
   noecho.c_lflag &= ~ECHO;
   if(tcsetattr(outfd, TCSANOW, &noecho) != 0)
   {
-    perror("tcgetattr");
+    ; /*perror("tcgetattr");*/
   }
 #else
 #  ifdef HAVE_TERMIO_H
   if(ioctl(outfd, TCGETA, &orig) != 0)
   {
-    perror("ioctl");
+    ; /*perror("ioctl");*/
   }
   noecho = orig;
   noecho.c_lflag &= ~ECHO;
   if(ioctl(outfd, TCSETA, &noecho) != 0)
   {
-    perror("ioctl");
+    ; /*perror("ioctl");*/
   }
 #  else
 #  endif
 #endif
 
   fputs(prompt, outfp);
   fflush(outfp);
 
-  bytes_read=read(infd, buf, INPUT_BUFFER);
-  buf[bytes_read > 0 ? (bytes_read -1) : 0] = '\0';
+  bytes_read=read(infd, buffer, buflen);
+  buffer[bytes_read > 0 ? (bytes_read -1) : 0] = '\0';
 
   /* print a new line if needed */
 #ifdef HAVE_TERMIOS_H
   fputs("\n", outfp);
 #else
 #  ifdef HAVE_TERMIO_H
