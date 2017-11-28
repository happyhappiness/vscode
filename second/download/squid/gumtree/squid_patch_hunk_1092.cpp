 
     hlp->last_queue_warn = squid_curtime;
 
     debugs(84, DBG_CRITICAL, "WARNING: All " << hlp->childs.n_active << "/" << hlp->childs.n_max << " " << hlp->id_name << " processes are busy.");
     debugs(84, DBG_CRITICAL, "WARNING: " << hlp->stats.queue_size << " pending requests queued");
     debugs(84, DBG_CRITICAL, "WARNING: Consider increasing the number of " << hlp->id_name << " processes in your config file.");
-
-    if (hlp->stats.queue_size > (int)hlp->childs.n_running * 2)
-        fatalf("Too many queued %s requests", hlp->id_name);
 }
 
 static void
-StatefulEnqueue(statefulhelper * hlp, Helper::Request * r)
+StatefulEnqueue(statefulhelper * hlp, Helper::Xaction * r)
 {
-    dlink_node *link = (dlink_node *)memAllocate(MEM_DLINK_NODE);
-    dlinkAddTail(r, link, &hlp->queue);
+    hlp->queue.push(r);
     ++ hlp->stats.queue_size;
 
     /* do this first so idle=N has a chance to grow the child pool before it hits critical. */
     if (hlp->childs.needNew() > 0) {
         debugs(84, DBG_CRITICAL, "Starting new " << hlp->id_name << " helpers...");
         helperStatefulOpenServers(hlp);
         return;
     }
 
-    if (hlp->stats.queue_size < (int)hlp->childs.n_running)
+    if (hlp->stats.queue_size < (int)hlp->childs.queue_size)
         return;
 
-    if (hlp->stats.queue_size > (int)hlp->childs.n_running * 2)
-        fatalf("Too many queued %s requests", hlp->id_name);
-
     if (squid_curtime - hlp->last_queue_warn < 600)
         return;
 
     if (shutting_down || reconfiguring)
         return;
 
