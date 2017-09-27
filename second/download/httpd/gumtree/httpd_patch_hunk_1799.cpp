     char buf[120];
 
     fprintf(stderr,
         "%s: %s (%d)\n",
         s, apr_strerror(rv, buf, sizeof buf), rv);
     if (done)
-        printf("Total of %ld requests completed\n" , done);
+        printf("Total of %d requests completed\n" , done);
     exit(rv);
 }
 
 /* --------------------------------------------------------- */
 /* write out request to a connection - assumes we can write
  * (small) request out in one go into our new socket buffer
