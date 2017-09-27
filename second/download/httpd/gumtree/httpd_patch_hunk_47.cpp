 
 static char *getpass(const char *prompt)
 {
 /* WCE lacks console. So the getpass is unsuported
  * The only way is to use the GUI so the getpass should be implemented
  * on per-application basis.
-*/ 
+ */ 
 #ifdef _WIN32_WCE
     return NULL;
 #else
-    static char password[MAX_STRING_LEN];
+    static char password[128];
     int n = 0;
+    int ch;
 
     fputs(prompt, stderr);
     
-    while ((password[n] = _getch()) != '\r') {
-        if (n < sizeof(password) - 1 && password[n] >= ' ' && password[n] <= '~') {
-            n++;
-            printf("*");
+    while ((ch = _getch()) != '\r') {
+        if (ch == EOF) /* EOF */ {
+            fputs("[EOF]\n", stderr);
+            return NULL;
         }
-	else {
-            printf("\n");
+        else if (ch == 0 || ch == 0xE0) {
+            /* FN Keys (0 or E0) are a sentinal for a FN code */ 
+            ch = (ch << 4) | _getch();
+            /* Catch {DELETE}, {<--}, Num{DEL} and Num{<--} */
+            if ((ch == 0xE53 || ch == 0xE4B || ch == 0x053 || ch == 0x04b) && n) {
+                password[--n] = '\0';
+                fputs("\b \b", stderr);
+            }
+            else {
+                fputc('\a', stderr);
+            }
+        }
+        else if ((ch == '\b' || ch == 127) && n) /* BS/DEL */ {
+            password[--n] = '\0';
+            fputs("\b \b", stderr);
+        }
+        else if (ch == 3) /* CTRL+C */ {
+            /* _getch() bypasses Ctrl+C but not Ctrl+Break detection! */
+            fputs("^C\n", stderr);
+            exit(-1);
+        }
+        else if (ch == 26) /* CTRL+Z */ {
+            fputs("^Z\n", stderr);
+            return NULL;
+        }
+	else if (ch == 27) /* ESC */ {
+            fputc('\n', stderr);
             fputs(prompt, stderr);
             n = 0;
         }
+        else if ((n < sizeof(password) - 1) && !apr_iscntrl(ch)) {
+            password[n++] = ch;
+            fputc('*', stderr);
+        }
+	else {
+            fputc('\a', stderr);
+        }
     }
  
+    fputc('\n', stderr);
     password[n] = '\0';
-    printf("\n");
-
-    if (n > (MAX_STRING_LEN - 1)) {
-        password[MAX_STRING_LEN - 1] = '\0';
-    }
-
-    return (char *) &password;
+    return password;
 #endif
 }
 
 #endif /* no getchar or _getch */
 
 #endif /* no getpass */
