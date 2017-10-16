   else
     password[0]=0; /* got nothing */
 
   if(disabled) {
     /* if echo actually was disabled, add a newline */
     fputs("\n", stderr);
-    ttyecho(TRUE, fd); /* enable echo */
+    (void)ttyecho(TRUE, fd); /* enable echo */
   }
 
   if(1 != fd)
     close(fd);
 
   return password; /* return pointer to buffer */
