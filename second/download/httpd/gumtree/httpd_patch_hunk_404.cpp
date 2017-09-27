         else {
             fprintf(stderr, "%s:%s:%s\n", h->username, h->userpass,
                     h->comment);
         }
     }
     htdbm_terminate(h);
-    apr_terminate();
     
     return 0; /* Suppress compiler warning. */
 }
