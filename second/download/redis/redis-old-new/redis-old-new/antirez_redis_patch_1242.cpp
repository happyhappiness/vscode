@@ -50,15 +50,15 @@ static int evport_debug = 0;
  * aeApiPoll, the corresponding file descriptors become dissociated from the
  * port.  This is necessary because poll events are level-triggered, so if the
  * fd didn't become dissociated, it would immediately fire another event since
- * the underlying state hasn't changed yet.  We must reassociate the file
+ * the underlying state hasn't changed yet.  We must re-associate the file
  * descriptor, but only after we know that our caller has actually read from it.
  * The ae API does not tell us exactly when that happens, but we do know that
  * it must happen by the time aeApiPoll is called again.  Our solution is to
- * keep track of the last fds returned by aeApiPoll and reassociate them next
+ * keep track of the last fds returned by aeApiPoll and re-associate them next
  * time aeApiPoll is invoked.
  *
  * To summarize, in this module, each fd association is EITHER (a) represented
- * only via the in-kernel assocation OR (b) represented by pending_fds and
+ * only via the in-kernel association OR (b) represented by pending_fds and
  * pending_masks.  (b) is only true for the last fds we returned from aeApiPoll,
  * and only until we enter aeApiPoll again (at which point we restore the
  * in-kernel association).
@@ -164,7 +164,7 @@ static int aeApiAddEvent(aeEventLoop *eventLoop, int fd, int mask) {
          * This fd was recently returned from aeApiPoll.  It should be safe to
          * assume that the consumer has processed that poll event, but we play
          * it safer by simply updating pending_mask.  The fd will be
-         * reassociated as usual when aeApiPoll is called again.
+         * re-associated as usual when aeApiPoll is called again.
          */
         if (evport_debug)
             fprintf(stderr, "aeApiAddEvent: adding to pending fd %d\n", fd);
@@ -228,7 +228,7 @@ static void aeApiDelEvent(aeEventLoop *eventLoop, int fd, int mask) {
          * ENOMEM is a potentially transient condition, but the kernel won't
          * generally return it unless things are really bad.  EAGAIN indicates
          * we've reached an resource limit, for which it doesn't make sense to
-         * retry (counterintuitively).  All other errors indicate a bug.  In any
+         * retry (counter-intuitively).  All other errors indicate a bug.  In any
          * of these cases, the best we can do is to abort.
          */
         abort(); /* will not return */
@@ -243,7 +243,7 @@ static int aeApiPoll(aeEventLoop *eventLoop, struct timeval *tvp) {
     port_event_t event[MAX_EVENT_BATCHSZ];
 
     /*
-     * If we've returned fd events before, we must reassociate them with the
+     * If we've returned fd events before, we must re-associate them with the
      * port now, before calling port_get().  See the block comment at the top of
      * this file for an explanation of why.
      */