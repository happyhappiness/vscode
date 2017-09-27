 #endif /* APR_CHARSET_EBCDIC */
 
 #define MAX_STRING_LEN 256
 
 #define ERR_OVERFLOW 5
 
-#if !defined(HAVE_GETPASS) && !defined(HAVE_GETPASSPHRASE) && !defined(HAVE_GETPASS_R)
+#ifndef HAVE_GETPASS
 
 /* MPE, Win32, NetWare and BeOS all lack a native getpass() */
 
 #if !defined(HAVE_TERMIOS_H) && !defined(WIN32) && !defined(NETWARE)
 /*
  * MPE lacks getpass() and a way to suppress stdin echo.  So for now, just
  * issue the prompt and read the results with echo.  (Ugh).
  */
 
-static char *get_password(const char *prompt)
+static char *getpass(const char *prompt)
 {
     static char password[MAX_STRING_LEN];
 
     fputs(prompt, stderr);
     fgets((char *) &password, sizeof(password), stdin);
 
     return (char *) &password;
 }
 
 #elif defined (HAVE_TERMIOS_H)
 #include <stdio.h>
 
-static char *get_password(const char *prompt)
+static char *getpass(const char *prompt)
 {
     struct termios attr;
     static char password[MAX_STRING_LEN];
     int n=0;
     fputs(prompt, stderr);
     fflush(stderr);
-
+	
     if (tcgetattr(STDIN_FILENO, &attr) != 0)
         return NULL;
     attr.c_lflag &= ~(ECHO);
 
     if (tcsetattr(STDIN_FILENO, TCSAFLUSH, &attr) != 0)
-        return NULL;
+	    return NULL;
     while ((password[n] = getchar()) != '\n') {
         if (n < sizeof(password) - 1 && password[n] >= ' ' && password[n] <= '~') {
             n++;
         } else {
             fprintf(stderr,"\n");
             fputs(prompt, stderr);
