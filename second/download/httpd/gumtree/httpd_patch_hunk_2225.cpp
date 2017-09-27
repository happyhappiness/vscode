         else if (c->bread != doclen) {
             bad++;
             err_length++;
         }
         /* save out time */
         if (done < requests) {
-            struct data s;
-            if ((done) && heartbeatres && !(done % heartbeatres)) {
-                fprintf(stderr, "Completed %ld requests\n", done);
+            struct data *s = &stats[done++];
+            c->done      = lasttime = apr_time_now();
+            s->starttime = c->start;
+            s->ctime     = ap_max(0, c->connect - c->start);
+            s->time      = ap_max(0, c->done - c->start);
+            s->waittime  = ap_max(0, c->beginread - c->endwrite);
+            if (heartbeatres && !(done % heartbeatres)) {
+                fprintf(stderr, "Completed %d requests\n", done);
                 fflush(stderr);
             }
-            c->done = apr_time_now();
-            s.read = c->read;
-            s.starttime = c->start;
-            s.ctime = ap_max(0, (c->connect - c->start) / 1000);
-            s.time = ap_max(0, (c->done - c->start) / 1000);
-            s.waittime = ap_max(0, (c->beginread - c->endwrite) / 1000);
-            stats[done++] = s;
         }
     }
 
     {
         apr_pollfd_t remove_pollfd;
         remove_pollfd.desc_type = APR_POLL_SOCKET;
