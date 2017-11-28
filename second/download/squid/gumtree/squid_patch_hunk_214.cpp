     if (count || valid_id)
         storeAppendPrintf(sentry, "%2d\t %-20s\t %5d\t %6.2f\n",
                           id, name, count, xdiv(count, dump_stat->scParsedCount));
 }
 
 HttpHdrScTarget *
-httpHdrScFindTarget (HttpHdrSc *sc, const char *target)
+HttpHdrSc::findTarget(const char *target)
 {
     dlink_node *node;
-    assert (sc);
-    node = sc->targets.head;
+    node = targets.head;
 
     while (node) {
         HttpHdrScTarget *sct = (HttpHdrScTarget *)node->data;
 
         if (target && sct->target.defined() && !strcmp (target, sct->target.termedBuf()))
             return sct;
