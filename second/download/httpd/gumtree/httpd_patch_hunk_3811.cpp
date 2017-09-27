     if ((rv = ssl_init_Engine(base_server, p)) != APR_SUCCESS) {
         return rv;
     }
 #endif
 
     ap_log_error(APLOG_MARK, APLOG_INFO, 0, s, APLOGNO(01883)
-                 "Init: Initialized %s library", SSL_LIBRARY_NAME);
+                 "Init: Initialized %s library", MODSSL_LIBRARY_NAME);
 
     /*
      * Seed the Pseudo Random Number Generator (PRNG)
      * only need ptemp here; nothing inside allocated from the pool
      * needs to live once we return from ssl_rand_seed().
      */
