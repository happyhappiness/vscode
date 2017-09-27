 	char *buff = malloc(postlen + reqlen + 1);
         if (!buff) {
             fprintf(stderr, "error creating request buffer: out of memory\n");
             return;
         }
 	strcpy(buff, request);
-	strcpy(buff + reqlen, postdata);
+        memcpy(buff + reqlen, postdata, postlen);
 	request = buff;
     }
 
 #ifdef NOT_ASCII
     inbytes_left = outbytes_left = reqlen;
     status = apr_xlate_conv_buffer(to_ascii, request, &inbytes_left,
-				   request, &outbytes_left);
+                   request, &outbytes_left);
     if (status || inbytes_left || outbytes_left) {
 	fprintf(stderr, "only simple translation is supported (%d/%u/%u)\n",
-		status, inbytes_left, outbytes_left);
+           status, inbytes_left, outbytes_left);
 	exit(1);
     }
-#endif				/* NOT_ASCII */
+#endif              /* NOT_ASCII */
 
     /* This only needs to be done once */
-#ifdef USE_SSL
-    if (ssl != 1)
-#endif
     if ((rv = apr_sockaddr_info_get(&destsa, connecthost, APR_UNSPEC, connectport, 0, cntxt))
-	!= APR_SUCCESS) {
+       != APR_SUCCESS) {
 	char buf[120];
 	apr_snprintf(buf, sizeof(buf),
-		     "apr_sockaddr_info_get() for %s", connecthost);
+                 "apr_sockaddr_info_get() for %s", connecthost);
 	apr_err(buf, rv);
     }
 
     /* ok - lets start */
     start = apr_time_now();
 
