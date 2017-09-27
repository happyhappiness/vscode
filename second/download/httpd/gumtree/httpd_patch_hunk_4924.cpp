 #endif
         "://]hostname[:port]/path\n", progname);
 /* 80 column ruler:  ********************************************************************************
  */
     fprintf(stderr, "Options are:\n");
     fprintf(stderr, "    -n requests     Number of requests to perform\n");
-    fprintf(stderr, "    -c concurrency  Number of multiple requests to make\n");
-    fprintf(stderr, "    -t timelimit    Seconds to max. wait for responses\n");
+    fprintf(stderr, "    -c concurrency  Number of multiple requests to make at a time\n");
+    fprintf(stderr, "    -t timelimit    Seconds to max. to spend on benchmarking\n");
+    fprintf(stderr, "                    This implies -n 50000\n");
+    fprintf(stderr, "    -s timeout      Seconds to max. wait for each response\n");
+    fprintf(stderr, "                    Default is 30 seconds\n");
     fprintf(stderr, "    -b windowsize   Size of TCP send/receive buffer, in bytes\n");
     fprintf(stderr, "    -B address      Address to bind to when making outgoing connections\n");
     fprintf(stderr, "    -p postfile     File containing data to POST. Remember also to set -T\n");
     fprintf(stderr, "    -u putfile      File containing data to PUT. Remember also to set -T\n");
-    fprintf(stderr, "    -T content-type Content-type header for POSTing, eg.\n");
+    fprintf(stderr, "    -T content-type Content-type header to use for POST/PUT data, eg.\n");
     fprintf(stderr, "                    'application/x-www-form-urlencoded'\n");
     fprintf(stderr, "                    Default is 'text/plain'\n");
     fprintf(stderr, "    -v verbosity    How much troubleshooting info to print\n");
     fprintf(stderr, "    -w              Print out results in HTML tables\n");
     fprintf(stderr, "    -i              Use HEAD instead of GET\n");
     fprintf(stderr, "    -x attributes   String to insert as table attributes\n");
