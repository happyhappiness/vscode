     UCHAR *ucp;
     apr_status_t rv;
 
     /* streamline session data */
     if ((nData = i2d_SSL_SESSION(sess, NULL)) > sizeof(ucaData)) {
         ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, s,
-                 "streamline session data size too large: %d > %d",
-                 nData, sizeof(ucaData));
+                     "streamline session data size too large: %d > "
+                     "%" APR_SIZE_T_FMT,
+                     nData, sizeof(ucaData));
         return FALSE;
     }
     ucp = ucaData;
     i2d_SSL_SESSION(sess, &ucp);
 
     /* be careful: do not try to store too much bytes in a DBM file! */
