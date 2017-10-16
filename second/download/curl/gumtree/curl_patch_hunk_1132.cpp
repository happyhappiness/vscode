 
   return PARAM_OK;
 }
 
 int ftpfilemethod(struct OperationConfig *config, const char *str)
 {
-  if(curlx_raw_equal("singlecwd", str))
+  if(curl_strequal("singlecwd", str))
     return CURLFTPMETHOD_SINGLECWD;
-  if(curlx_raw_equal("nocwd", str))
+  if(curl_strequal("nocwd", str))
     return CURLFTPMETHOD_NOCWD;
-  if(curlx_raw_equal("multicwd", str))
+  if(curl_strequal("multicwd", str))
     return CURLFTPMETHOD_MULTICWD;
 
   warnf(config->global, "unrecognized ftp file method '%s', using default\n",
         str);
 
   return CURLFTPMETHOD_MULTICWD;
 }
 
 int ftpcccmethod(struct OperationConfig *config, const char *str)
 {
-  if(curlx_raw_equal("passive", str))
+  if(curl_strequal("passive", str))
     return CURLFTPSSL_CCC_PASSIVE;
-  if(curlx_raw_equal("active", str))
+  if(curl_strequal("active", str))
     return CURLFTPSSL_CCC_ACTIVE;
 
   warnf(config->global, "unrecognized ftp CCC method '%s', using default\n",
         str);
 
   return CURLFTPSSL_CCC_PASSIVE;
 }
 
 long delegation(struct OperationConfig *config, char *str)
 {
-  if(curlx_raw_equal("none", str))
+  if(curl_strequal("none", str))
     return CURLGSSAPI_DELEGATION_NONE;
-  if(curlx_raw_equal("policy", str))
+  if(curl_strequal("policy", str))
     return CURLGSSAPI_DELEGATION_POLICY_FLAG;
-  if(curlx_raw_equal("always", str))
+  if(curl_strequal("always", str))
     return CURLGSSAPI_DELEGATION_FLAG;
 
   warnf(config->global, "unrecognized delegation method '%s', using none\n",
         str);
 
   return CURLGSSAPI_DELEGATION_NONE;
