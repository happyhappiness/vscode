   }
 #else
   (void)str;
 #endif
 }
 
+/*
+ * Parse the string and write the integer in the given address. Return
+ * non-zero on failure, zero on success.
+ *
+ * The string must start with a digit to be valid.
+ */
+
+static int str2num(long *val, char *str)
+{
+  int retcode = 0;
+  if(isdigit((int)*str))
+    *val = atoi(str);
+  else
+    retcode = 1; /* badness */
+  return retcode;  
+}
+
+static void checkpasswd(const char *kind, /* for what purpose */
+                        char **userpwd) /* pointer to allocated string */
+{
+  char *ptr = strchr(*userpwd, ':');
+  if(!ptr) {
+    /* no password present, prompt for one */
+    char passwd[256]="";
+    char prompt[256];
+    int passwdlen;
+    int userlen = strlen(*userpwd);
+    char *ptr;
+
+    /* build a nice-looking prompt */
+    curl_msnprintf(prompt, sizeof(prompt),
+                   "Enter %s password for user '%s':",
+                   kind, *userpwd);
+
+    /* get password */
+    getpass_r(prompt, passwd, sizeof(passwd));
+    passwdlen = strlen(passwd);
+
+    /* extend the allocated memory are to fit the password too */
+    ptr = realloc(*userpwd,
+                  passwdlen + 1 + /* an extra for the colon */
+                  userlen + 1);   /* an extra for the zero */
+
+    if(ptr) {
+      /* append the password separated with a colon */
+      ptr[userlen]=':';
+      memcpy(&ptr[userlen+1], passwd, passwdlen+1);
+      *userpwd = ptr;
+    }
+  }
+}
+
 static ParameterError getparameter(char *flag, /* f or -long-flag */
                                    char *nextarg, /* NULL if unset */
                                    bool *usedarg, /* set to TRUE if the arg
                                                      has been used */
                                    struct Configurable *config)
 {
