   if(curlx_strequal("multicwd", str))
     return CURLFTPMETHOD_MULTICWD;
   warnf(config, "unrecognized ftp file method '%s', using default\n", str);
   return CURLFTPMETHOD_MULTICWD;
 }
 
+static int ftpcccmethod(struct Configurable *config, char *str)
+{
+  if(curlx_strequal("passive", str))
+    return CURLFTPSSL_CCC_PASSIVE;
+  if(curlx_strequal("active", str))
+    return CURLFTPSSL_CCC_ACTIVE;
+  warnf(config, "unrecognized ftp CCC method '%s', using default\n", str);
+  return CURLFTPSSL_CCC_PASSIVE;
+}
+
 static ParameterError getparameter(char *flag, /* f or -long-flag */
                                    char *nextarg, /* NULL if unset */
                                    bool *usedarg, /* set to TRUE if the arg
                                                      has been used */
                                    struct Configurable *config)
 {
