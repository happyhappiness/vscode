     timetaken = ((float)apr_time_sec(timetakenusec)) +
         ((float)apr_time_usec(timetakenusec)) / 1000000.0F;
 
     printf("\n\n");
     printf("Server Software:        %s\n", servername);
     printf("Server Hostname:        %s\n", hostname);
-    printf("Server Port:            %hd\n", port);
+    printf("Server Port:            %hu\n", port);
 #ifdef USE_SSL
     if (is_ssl && ssl_info) {
         printf("SSL/TLS Protocol:       %s\n", ssl_info);
     }
 #endif
     printf("\n");
