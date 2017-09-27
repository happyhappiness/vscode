  * @param r The current request
  * @return The number of bytes sent
  * @note ap_rputs may be implemented as macro or inline function
  */
 static APR_INLINE int ap_rputs(const char *str, request_rec *r)
 {
-    return ap_rwrite(str, strlen(str), r);
+    return ap_rwrite(str, (int)strlen(str), r);
 }
 
 /**
  * Write an unspecified number of strings to the request
  * @param r The current request
  * @param ... The strings to write
