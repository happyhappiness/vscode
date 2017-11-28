 
         if (e->stats.last_connect_failure) {
             storeAppendPrintf(sentry, "Last failed connect() at: %s\n",
                               Time::FormatHttpd(e->stats.last_connect_failure));
         }
 
-        if (e->peer_domain != NULL) {
-            storeAppendPrintf(sentry, "DOMAIN LIST: ");
-
-            for (d = e->peer_domain; d; d = d->next) {
-                storeAppendPrintf(sentry, "%s%s ",
-                                  d->do_ping ? null_string : "!", d->domain);
-            }
-
-            storeAppendPrintf(sentry, "\n");
-        }
-
         storeAppendPrintf(sentry, "keep-alive ratio: %d%%\n", Math::intPercent(e->stats.n_keepalives_recv, e->stats.n_keepalives_sent));
     }
 }
 
 #if USE_HTCP
 void
