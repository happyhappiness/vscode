   else
     return PARAM_NO_MEM;
 
   return PARAM_OK;
 }
 
+static int ftpfilemethod(struct Configurable *config, char *str)
+{
+  if(curlx_strequal("singlecwd", str))
+    return CURLFTPMETHOD_SINGLECWD;
+  if(curlx_strequal("nocwd", str))
+    return CURLFTPMETHOD_NOCWD;
+  if(curlx_strequal("multicwd", str))
+    return CURLFTPMETHOD_MULTICWD;
+  warnf(config, "unrecognized ftp file method '%s', using default\n", str);
+  return CURLFTPMETHOD_MULTICWD;
+}
+
 static ParameterError getparameter(char *flag, /* f or -long-flag */
                                    char *nextarg, /* NULL if unset */
                                    bool *usedarg, /* set to TRUE if the arg
                                                      has been used */
                                    struct Configurable *config)
 {
   char letter;
   char subletter=0; /* subletters can only occur on long options */
-
+  int rc; /* generic return code variable */
   const char *parse=NULL;
   unsigned int j;
   time_t now;
   int hit=-1;
   bool longopt=FALSE;
   bool singleopt=FALSE; /* when true means '-o foo' used '-ofoo' */
