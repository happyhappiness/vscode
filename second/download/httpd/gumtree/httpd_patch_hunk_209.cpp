     if ((result = apr_file_read(fd, (char *) buf, &nbytes)) != APR_SUCCESS) {
 	ap_log_rerror(APLOG_MARK, APLOG_ERR, result, r,
 		    MODNAME ": read failed: %s", r->filename);
 	return HTTP_INTERNAL_SERVER_ERROR;
     }
 
-    if (nbytes == 0)
-	magic_rsl_puts(r, MIME_TEXT_UNKNOWN);
+    if (nbytes == 0) {
+        return DECLINED;
+    }
     else {
 	buf[nbytes++] = '\0';	/* null-terminate it */
-	tryit(r, buf, nbytes, 1); 
+        result = tryit(r, buf, nbytes, 1);
+	if (result != OK) {
+            return result;
+        }
     }
 
     (void) apr_file_close(fd);
     (void) magic_rsl_putchar(r, '\n');
 
     return OK;
 }
 
 
-static void tryit(request_rec *r, unsigned char *buf, apr_size_t nb, int checkzmagic)
+static int tryit(request_rec *r, unsigned char *buf, apr_size_t nb,
+                 int checkzmagic)
 {
     /*
      * Try compression stuff
      */
 	if (checkzmagic == 1) {  
 			if (zmagic(r, buf, nb) == 1)
-			return;
+			return OK;
 	}
 
     /*
      * try tests in /etc/magic (or surrogate magic file)
      */
     if (softmagic(r, buf, nb) == 1)
-	return;
+	return OK;
 
     /*
      * try known keywords, check for ascii-ness too.
      */
     if (ascmagic(r, buf, nb) == 1)
-	return;
+	return OK;
 
     /*
      * abandon hope, all ye who remain here
      */
-    magic_rsl_puts(r, MIME_BINARY_UNKNOWN);
+    return DECLINED;
 }
 
 #define    EATAB {while (apr_isspace(*l))  ++l;}
 
 /*
  * apprentice - load configuration from the magic file r
