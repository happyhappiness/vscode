@@ -1,25 +1,25 @@
-/*****************************************************************************
+/***************************************************************************
  *                                  _   _ ____  _     
  *  Project                     ___| | | |  _ \| |    
  *                             / __| | | | |_) | |    
  *                            | (__| |_| |  _ <| |___ 
  *                             \___|\___/|_| \_\_____|
  *
- * Copyright (C) 2000, Daniel Stenberg, <daniel@haxx.se>, et al.
- *
- * In order to be useful for every potential user, curl and libcurl are
- * dual-licensed under the MPL and the MIT/X-derivate licenses.
+ * Copyright (C) 1998 - 2002, Daniel Stenberg, <daniel@haxx.se>, et al.
  *
+ * This software is licensed as described in the file COPYING, which
+ * you should have received as part of this distribution. The terms
+ * are also available at http://curl.haxx.se/docs/copyright.html.
+ * 
  * You may opt to use, copy, modify, merge, publish, distribute and/or sell
  * copies of the Software, and permit persons to whom the Software is
- * furnished to do so, under the terms of the MPL or the MIT/X-derivate
- * licenses. You may pick one of these licenses.
+ * furnished to do so, under the terms of the COPYING file.
  *
  * This software is distributed on an "AS IS" basis, WITHOUT WARRANTY OF ANY
  * KIND, either express or implied.
  *
  * $Id$
- *****************************************************************************/
+ ***************************************************************************/
 
 #include "setup.h"
 
@@ -78,12 +78,15 @@ int Curl_parsenetrc(char *host,
   FILE *file;
   char netrcbuffer[256];
   int retcode=1;
+
+  int specific_login = (login[0] != 0);
   
   char *home = NULL; 
   int state=NOTHING;
 
-  char state_login=0;
-  char state_password=0;
+  char state_login=0;      /* Found a login keyword */
+  char state_password=0;   /* Found a password keyword */
+  char state_our_login=0;  /* With specific_login, found *our* login name */
 
 #define NETRC DOT_CHAR "netrc"
 
@@ -116,13 +119,41 @@ int Curl_parsenetrc(char *host,
 
   sprintf(netrcbuffer, "%s%s%s", home, DIR_CHAR, NETRC);
 
+#ifdef MALLOCDEBUG
+  {
+    /* This is a hack to allow testing.
+     * If compiled with --enable-debug and CURL_DEBUG_NETRC is defined,
+     * then it's the path to a substitute .netrc for testing purposes *only* */
+
+    char *override = curl_getenv("CURL_DEBUG_NETRC");
+
+    if (override != NULL) {
+      printf("NETRC: overridden .netrc file: %s\n", home);
+
+      if (strlen(override)+1 > sizeof(netrcbuffer)) {
+        free(override);
+        if(NULL==pw)
+          free(home);
+
+        return -1;
+      }
+      strcpy(netrcbuffer, override);
+      free(override);
+    }
+  }
+#endif /* MALLOCDEBUG */
+
   file = fopen(netrcbuffer, "r");
   if(file) {
     char *tok;
         char *tok_buf;
     while(fgets(netrcbuffer, sizeof(netrcbuffer), file)) {
       tok=strtok_r(netrcbuffer, " \t\n", &tok_buf);
       while(tok) {
+
+        if (login[0] && password[0])
+          goto done;
+
         switch(state) {
         case NOTHING:
           if(strequal("machine", tok)) {
@@ -149,17 +180,23 @@ int Curl_parsenetrc(char *host,
         case HOSTVALID:
           /* we are now parsing sub-keywords concerning "our" host */
           if(state_login) {
-            strncpy(login, tok, LOGINSIZE-1);
+            if (specific_login) {
+              state_our_login = strequal(login, tok);
+            }else{
+              strncpy(login, tok, LOGINSIZE-1);
 #ifdef _NETRC_DEBUG
-            printf("LOGIN: %s\n", login);
+              printf("LOGIN: %s\n", login);
 #endif
+            }
             state_login=0;
           }
           else if(state_password) {
-            strncpy(password, tok, PASSWORDSIZE-1);
+            if (state_our_login || !specific_login) {
+              strncpy(password, tok, PASSWORDSIZE-1);
 #ifdef _NETRC_DEBUG
-            printf("PASSWORD: %s\n", password);
+              printf("PASSWORD: %s\n", password);
 #endif
+            }
             state_password=0;
           }
           else if(strequal("login", tok))
@@ -169,13 +206,16 @@ int Curl_parsenetrc(char *host,
           else if(strequal("machine", tok)) {
             /* ok, there's machine here go => */
             state = HOSTFOUND;
+            state_our_login = 0;
           }
           break;
         } /* switch (state) */
+
         tok = strtok_r(NULL, " \t\n", &tok_buf);
       } /* while (tok) */
     } /* while fgets() */
 
+done:
     fclose(file);
   }
 