     if (buffer_output(r, &c2, 1) != APR_SUCCESS)
         return -1;
 
     return c;
 }
 
-AP_DECLARE(int) ap_rputs(const char *str, request_rec *r)
-{
-    apr_size_t len;
-
-    if (r->connection->aborted)
-        return -1;
-
-    if (buffer_output(r, str, len = strlen(str)) != APR_SUCCESS)
-        return -1;
-
-    return len;
-}
-
 AP_DECLARE(int) ap_rwrite(const void *buf, int nbyte, request_rec *r)
 {
     if (r->connection->aborted)
         return -1;
 
     if (buffer_output(r, buf, nbyte) != APR_SUCCESS)
