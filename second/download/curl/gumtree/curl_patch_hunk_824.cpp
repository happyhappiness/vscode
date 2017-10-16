   else
     return PARAM_NO_MEM;
 
   return PARAM_OK;
 }
 
-int ftpfilemethod(struct Configurable *config, const char *str)
+int ftpfilemethod(struct OperationConfig *config, const char *str)
 {
   if(curlx_raw_equal("singlecwd", str))
     return CURLFTPMETHOD_SINGLECWD;
   if(curlx_raw_equal("nocwd", str))
     return CURLFTPMETHOD_NOCWD;
   if(curlx_raw_equal("multicwd", str))
     return CURLFTPMETHOD_MULTICWD;
   warnf(config, "unrecognized ftp file method '%s', using default\n", str);
   return CURLFTPMETHOD_MULTICWD;
 }
 
-int ftpcccmethod(struct Configurable *config, const char *str)
+int ftpcccmethod(struct OperationConfig *config, const char *str)
 {
   if(curlx_raw_equal("passive", str))
     return CURLFTPSSL_CCC_PASSIVE;
   if(curlx_raw_equal("active", str))
     return CURLFTPSSL_CCC_ACTIVE;
   warnf(config, "unrecognized ftp CCC method '%s', using default\n", str);
   return CURLFTPSSL_CCC_PASSIVE;
 }
 
-long delegation(struct Configurable *config, char *str)
+long delegation(struct OperationConfig *config, char *str)
 {
   if(curlx_raw_equal("none", str))
     return CURLGSSAPI_DELEGATION_NONE;
   if(curlx_raw_equal("policy", str))
     return CURLGSSAPI_DELEGATION_POLICY_FLAG;
   if(curlx_raw_equal("always", str))
     return CURLGSSAPI_DELEGATION_FLAG;
   warnf(config, "unrecognized delegation method '%s', using none\n", str);
   return CURLGSSAPI_DELEGATION_NONE;
 }
 
+/*
+ * my_useragent: returns allocated string with default user agent
+ */
+static char *my_useragent(void)
+{
+  return strdup(CURL_NAME "/" CURL_VERSION);
+}
+
+CURLcode get_args(struct OperationConfig *config, const size_t i)
+{
+  CURLcode result = CURLE_OK;
+  bool last = (config->next ? FALSE : TRUE);
+
+  /* Check we have a password for the given host user */
+  if(config->userpwd && !config->xoauth2_bearer) {
+    result = checkpasswd("host", i, last, &config->userpwd);
+    if(result)
+      return result;
+  }
+
+  /* Check we have a password for the given proxy user */
+  if(config->proxyuserpwd) {
+    result = checkpasswd("proxy", i, last, &config->proxyuserpwd);
+    if(result)
+      return result;
+  }
+
+  /* Check we have a user agent */
+  if(!config->useragent) {
+    config->useragent = my_useragent();
+    if(!config->useragent) {
+      helpf(config->global->errors, "out of memory\n");
+      result = CURLE_OUT_OF_MEMORY;
+    }
+  }
+
+  return result;
+}
