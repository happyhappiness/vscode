             d = sdscatprintf(d, "%02x",digest[j]);
         addReplyStatus(c,d);
         sdsfree(d);
     } else if (!strcasecmp(c->argv[1]->ptr,"sleep") && c->argc == 3) {
         double dtime = strtod(c->argv[2]->ptr,NULL);
         long long utime = dtime*1000000;
+        struct timespec tv;
 
-        usleep(utime);
+        tv.tv_sec = utime / 1000000;
+        tv.tv_nsec = (utime % 1000000) * 1000;
+        nanosleep(&tv, NULL);
         addReply(c,shared.ok);
     } else if (!strcasecmp(c->argv[1]->ptr,"set-active-expire") &&
                c->argc == 3)
     {
         server.active_expire_enabled = atoi(c->argv[2]->ptr);
         addReply(c,shared.ok);
