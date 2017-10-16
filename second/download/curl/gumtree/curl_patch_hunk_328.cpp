 char *getpass_r(const char *prompt, char *buffer, size_t buflen)
 {
   size_t i;
   fputs(prompt, stderr);
 
   for(i=0; i<buflen; i++) {
-    buffer[i] = getch();
+    buffer[i] = (char)getch();
     if ( buffer[i] == '\r' || buffer[i] == '\n' ) {
       buffer[i] = 0;
       break;
     }
     else
       if ( buffer[i] == '\b')
