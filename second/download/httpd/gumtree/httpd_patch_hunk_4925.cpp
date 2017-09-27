     fprintf(stderr, "                    are a colon separated username and password.\n");
     fprintf(stderr, "    -X proxy:port   Proxyserver and port number to use\n");
     fprintf(stderr, "    -V              Print version number and exit\n");
     fprintf(stderr, "    -k              Use HTTP KeepAlive feature\n");
     fprintf(stderr, "    -d              Do not show percentiles served table.\n");
     fprintf(stderr, "    -S              Do not show confidence estimators and warnings.\n");
+    fprintf(stderr, "    -q              Do not show progress when doing more than 150 requests\n");
     fprintf(stderr, "    -g filename     Output collected data to gnuplot format file.\n");
     fprintf(stderr, "    -e filename     Output CSV file with percentages served\n");
     fprintf(stderr, "    -r              Don't exit on socket receive errors.\n");
     fprintf(stderr, "    -h              Display usage information (this message)\n");
 #ifdef USE_SSL
-    fprintf(stderr, "    -Z ciphersuite  Specify SSL/TLS cipher suite (See openssl ciphers)\n");
+
 #ifndef OPENSSL_NO_SSL2
-    fprintf(stderr, "    -f protocol     Specify SSL/TLS protocol (SSL2, SSL3, TLS1, or ALL)\n");
+#define SSL2_HELP_MSG "SSL2, "
 #else
-    fprintf(stderr, "    -f protocol     Specify SSL/TLS protocol (SSL3, TLS1, or ALL)\n");
+#define SSL2_HELP_MSG ""
 #endif
+
+#ifdef HAVE_TLSV1_X
+#define TLS1_X_HELP_MSG ", TLS1.1, TLS1.2"
+#else
+#define TLS1_X_HELP_MSG ""
+#endif
+
+    fprintf(stderr, "    -Z ciphersuite  Specify SSL/TLS cipher suite (See openssl ciphers)\n");
+    fprintf(stderr, "    -f protocol     Specify SSL/TLS protocol\n"); 
+    fprintf(stderr, "                    (" SSL2_HELP_MSG "SSL3, TLS1" TLS1_X_HELP_MSG " or ALL)\n");
 #endif
     exit(EINVAL);
 }
 
 /* ------------------------------------------------------- */
 
