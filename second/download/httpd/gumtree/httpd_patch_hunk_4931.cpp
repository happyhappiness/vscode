         }
         fprintf(stdout, "Database %s %s.\n", h->filename,
                 h->create ? "created" : (changed ? "modified" : "updated"));
     }
     if (cmd == HTDBM_NOFILE) {
         if (!need_cmnt) {
-            fprintf(stderr, "%s:%s\n", h->username, h->userpass);
+            fprintf(stderr, "%s:%s\n", h->username, h->ctx.passwd);
         }
         else {
-            fprintf(stderr, "%s:%s:%s\n", h->username, h->userpass,
+            fprintf(stderr, "%s:%s:%s\n", h->username, h->ctx.passwd,
                     h->comment);
         }
     }
     htdbm_terminate(h);
 
     return 0; /* Suppress compiler warning. */
