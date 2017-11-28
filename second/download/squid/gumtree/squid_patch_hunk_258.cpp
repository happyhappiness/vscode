 void Ssl::Helper::Shutdown()
 {
     if (!ssl_crtd)
         return;
     helperShutdown(ssl_crtd);
     wordlistDestroy(&ssl_crtd->cmdline);
-    if (!shutting_down)
-        return;
-    helperFree(ssl_crtd);
+    delete ssl_crtd;
     ssl_crtd = NULL;
 }
 
 void Ssl::Helper::sslSubmit(CrtdMessage const & message, HLPCB * callback, void * data)
 {
     static time_t first_warn = 0;
+    assert(ssl_crtd);
 
-    if (ssl_crtd->stats.queue_size >= (int)(ssl_crtd->n_running * 2)) {
+    if (ssl_crtd->stats.queue_size >= (int)(ssl_crtd->childs.n_running * 2)) {
         if (first_warn == 0)
             first_warn = squid_curtime;
         if (squid_curtime - first_warn > 3 * 60)
             fatal("SSL servers not responding for 3 minutes");
         debugs(34, 1, HERE << "Queue overload, rejecting");
         callback(data, (char *)"error 45 Temporary network problem, please retry later");
