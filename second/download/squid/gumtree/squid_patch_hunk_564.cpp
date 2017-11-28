     storeAppendPrintf(sentry, "queue length: %d\n",
                       hlp->stats.queue_size);
     storeAppendPrintf(sentry, "avg service time: %d msec\n",
                       hlp->stats.avg_svc_time);
     storeAppendPrintf(sentry, "\n");
     storeAppendPrintf(sentry, "%7s\t%7s\t%7s\t%11s\t%11s\t%s\t%7s\t%7s\t%7s\n",
-                      "#",
+                      "ID #",
                       "FD",
                       "PID",
                       "# Requests",
                       "# Replies",
                       "Flags",
                       "Time",
                       "Offset",
                       "Request");
 
     for (dlink_node *link = hlp->servers.head; link; link = link->next) {
         helper_server *srv = (helper_server*)link->data;
         double tt = 0.001 * (srv->requests[0] ? tvSubMsec(srv->requests[0]->dispatch_time, current_time) : tvSubMsec(srv->dispatch_time, srv->answer_time));
-        storeAppendPrintf(sentry, "%7d\t%7d\t%7d\t%11" PRIu64 "\t%11" PRIu64 "\t%c%c%c%c\t%7.3f\t%7d\t%s\n",
-                          srv->index + 1,
+        storeAppendPrintf(sentry, "%7u\t%7d\t%7d\t%11" PRIu64 "\t%11" PRIu64 "\t%c%c%c%c\t%7.3f\t%7d\t%s\n",
+                          srv->index.value,
                           srv->readPipe->fd,
                           srv->pid,
                           srv->stats.uses,
                           srv->stats.replies,
                           srv->stats.pending ? 'B' : ' ',
                           srv->flags.writing ? 'W' : ' ',
