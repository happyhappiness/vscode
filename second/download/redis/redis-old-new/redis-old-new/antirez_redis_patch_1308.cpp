@@ -12,7 +12,7 @@
 
 #include <stdio.h>
 
-int evport_debug = 0;
+static int evport_debug = 0;
 
 /*
  * This file implements the ae API using event ports, present on Solaris-based
@@ -21,33 +21,33 @@ int evport_debug = 0;
  * events that the consumer is interested in (e.g., POLLIN and POLLOUT).
  *
  * There's one tricky piece to this implementation: when we return events via
- * aeApiPoll, the corresponding file descriptor becomes dissociated from the
+ * aeApiPoll, the corresponding file descriptors become dissociated from the
  * port.  This is necessary because poll events are level-triggered, so if the
  * fd didn't become dissociated, it would immediately fire another event since
  * the underlying state hasn't changed yet.  We must reassociate the file
  * descriptor, but only after we know that our caller has actually read from it.
  * The ae API does not tell us exactly when that happens, but we do know that
  * it must happen by the time aeApiPoll is called again.  Our solution is to
- * keep track of the last fd returned by aeApiPoll and reassociate it next time
- * aeApiPoll is invoked.
+ * keep track of the last fds returned by aeApiPoll and reassociate them next
+ * time aeApiPoll is invoked.
  *
  * To summarize, in this module, each fd association is EITHER (a) represented
- * only via the in-kernel assocation OR (b) represented by pending_fd and
- * pending_mask.  (b) is only true for the last fd we returned from aeApiPoll,
+ * only via the in-kernel assocation OR (b) represented by pending_fds and
+ * pending_masks.  (b) is only true for the last fds we returned from aeApiPoll,
  * and only until we enter aeApiPoll again (at which point we restore the
  * in-kernel association).
- *
- * We currently only return one fd event per call to aeApiPoll.  This could be
- * extended to return more than one by extending the corresponding pending
- * fields and using port_getn().
  */
+#define MAX_EVENT_BATCHSZ 512
+
 typedef struct aeApiState {
-    int     portfd;             /* event port */
-    int     pending_fd;         /* pending fd */
-    int     pending_mask;       /* pending fd's mask */
+    int     portfd;                             /* event port */
+    int     npending;                           /* # of pending fds */
+    int     pending_fds[MAX_EVENT_BATCHSZ];     /* pending fds */
+    int     pending_masks[MAX_EVENT_BATCHSZ];   /* pending fds' masks */
 } aeApiState;
 
 static int aeApiCreate(aeEventLoop *eventLoop) {
+    int i;
     aeApiState *state = zmalloc(sizeof(aeApiState));
     if (!state) return -1;
 
@@ -57,8 +57,12 @@ static int aeApiCreate(aeEventLoop *eventLoop) {
         return -1;
     }
 
-    state->pending_fd = -1;
-    state->pending_mask = AE_NONE;
+    state->npending = 0;
+
+    for (i = 0; i < MAX_EVENT_BATCHSZ; i++) {
+        state->pending_fds[i] = -1;
+        state->pending_masks[i] = AE_NONE;
+    }
 
     eventLoop->apidata = state;
     return 0;    
@@ -71,11 +75,21 @@ static void aeApiFree(aeEventLoop *eventLoop) {
     zfree(state);
 }
 
+static int aeApiLookupPending(aeApiState *state, int fd) {
+    int i;
+
+    for (i = 0; i < state->npending; i++) {
+        if (state->pending_fds[i] == fd)
+            return (i);
+    }
+
+    return (-1);
+}
+
 /*
  * Helper function to invoke port_associate for the given fd and mask.
  */
-static int aeApiAssociate(const char *where, int portfd, int fd, int mask)
-{
+static int aeApiAssociate(const char *where, int portfd, int fd, int mask) {
     int events = 0;
     int rv, err;
 
@@ -87,7 +101,8 @@ static int aeApiAssociate(const char *where, int portfd, int fd, int mask)
     if (evport_debug)
         fprintf(stderr, "%s: port_associate(%d, 0x%x) = ", where, fd, events);
 
-    rv = port_associate(portfd, PORT_SOURCE_FD, fd, events, (void *)mask);
+    rv = port_associate(portfd, PORT_SOURCE_FD, fd, events,
+        (void *)(uintptr_t)mask);
     err = errno;
 
     if (evport_debug)
@@ -105,7 +120,7 @@ static int aeApiAssociate(const char *where, int portfd, int fd, int mask)
 
 static int aeApiAddEvent(aeEventLoop *eventLoop, int fd, int mask) {
     aeApiState *state = eventLoop->apidata;
-    int fullmask;
+    int fullmask, pfd;
 
     if (evport_debug)
         fprintf(stderr, "aeApiAddEvent: fd %d mask 0x%x\n", fd, mask);
@@ -116,8 +131,9 @@ static int aeApiAddEvent(aeEventLoop *eventLoop, int fd, int mask) {
      * we call port_associate() again.
      */
     fullmask = mask | eventLoop->events[fd].mask;
+    pfd = aeApiLookupPending(state, fd);
 
-    if (fd == state->pending_fd) {
+    if (pfd != -1) {
         /*
          * This fd was recently returned from aeApiPoll.  It should be safe to
          * assume that the consumer has processed that poll event, but we play
@@ -126,7 +142,7 @@ static int aeApiAddEvent(aeEventLoop *eventLoop, int fd, int mask) {
          */
         if (evport_debug)
             fprintf(stderr, "aeApiAddEvent: adding to pending fd %d\n", fd);
-        state->pending_mask |= fullmask;
+        state->pending_masks[pfd] |= fullmask;
         return 0;
     }
 
@@ -135,12 +151,14 @@ static int aeApiAddEvent(aeEventLoop *eventLoop, int fd, int mask) {
 
 static void aeApiDelEvent(aeEventLoop *eventLoop, int fd, int mask) {
     aeApiState *state = eventLoop->apidata;
-    int fullmask;
+    int fullmask, pfd;
 
     if (evport_debug)
         fprintf(stderr, "del fd %d mask 0x%x\n", fd, mask);
 
-    if (fd == state->pending_fd) {
+    pfd = aeApiLookupPending(state, fd);
+
+    if (pfd != -1) {
         if (evport_debug)
             fprintf(stderr, "deleting event from pending fd %d\n", fd);
 
@@ -149,10 +167,10 @@ static void aeApiDelEvent(aeEventLoop *eventLoop, int fd, int mask) {
          * associated with the port.  All we need to do is update
          * pending_mask appropriately.
          */
-        state->pending_mask &= ~mask;
+        state->pending_masks[pfd] &= ~mask;
 
-        if (state->pending_mask == AE_NONE)
-            state->pending_fd = -1;
+        if (state->pending_masks[pfd] == AE_NONE)
+            state->pending_fds[pfd] = -1;
 
         return;
     }
@@ -194,25 +212,32 @@ static void aeApiDelEvent(aeEventLoop *eventLoop, int fd, int mask) {
 static int aeApiPoll(aeEventLoop *eventLoop, struct timeval *tvp) {
     aeApiState *state = eventLoop->apidata;
     struct timespec timeout, *tsp;
-    int mask;
-    port_event_t event;
+    int mask, i;
+    uint_t nevents;
+    port_event_t event[MAX_EVENT_BATCHSZ];
 
     /*
-     * If we've returned an fd event before, we must reassociated that fd with
-     * the port now, before calling port_get().  See the block comment at the
-     * top of this file for an explanation of why.
+     * If we've returned fd events before, we must reassociate them with the
+     * port now, before calling port_get().  See the block comment at the top of
+     * this file for an explanation of why.
      */
-    if (state->pending_mask != AE_NONE) {
-        if (aeApiAssociate("aeApiPoll", state->portfd, state->pending_fd,
-            state->pending_mask) != 0) {
+    for (i = 0; i < state->npending; i++) {
+        if (state->pending_fds[i] == -1)
+            /* This fd has since been deleted. */
+            continue;
+
+        if (aeApiAssociate("aeApiPoll", state->portfd,
+            state->pending_fds[i], state->pending_masks[i]) != 0) {
             /* See aeApiDelEvent for why this case is fatal. */
             abort();
         }
 
-        state->pending_mask = AE_NONE;
-        state->pending_fd = -1;
+        state->pending_masks[i] = AE_NONE;
+        state->pending_fds[i] = -1;
     }
 
+    state->npending = 0;
+
     if (tvp != NULL) {
         timeout.tv_sec = tvp->tv_sec;
         timeout.tv_nsec = tvp->tv_usec * 1000;
@@ -221,7 +246,13 @@ static int aeApiPoll(aeEventLoop *eventLoop, struct timeval *tvp) {
         tsp = NULL;
     }
 
-    if (port_get(state->portfd, &event, tsp) == -1) {
+    /*
+     * port_getn can return with errno == ETIME having returned some events (!). 
+     * So if we get ETIME, we check nevents, too.
+     */
+    nevents = 1;
+    if (port_getn(state->portfd, event, MAX_EVENT_BATCHSZ, &nevents,
+        tsp) == -1 && (errno != ETIME || nevents == 0)) {
         if (errno == ETIME || errno == EINTR)
             return 0;
 
@@ -230,23 +261,27 @@ static int aeApiPoll(aeEventLoop *eventLoop, struct timeval *tvp) {
         abort();
     }
 
-    mask = 0;
-    if (event.portev_events & POLLIN)
-        mask |= AE_READABLE;
-    if (event.portev_events & POLLOUT)
-        mask |= AE_WRITABLE;
+    state->npending = nevents;
 
-    eventLoop->fired[0].fd = event.portev_object;
-    eventLoop->fired[0].mask = mask;
+    for (i = 0; i < nevents; i++) {
+            mask = 0;
+            if (event[i].portev_events & POLLIN)
+                mask |= AE_READABLE;
+            if (event[i].portev_events & POLLOUT)
+                mask |= AE_WRITABLE;
 
-    if (evport_debug)
-        fprintf(stderr, "aeApiPoll: fd %d mask 0x%x\n", event.portev_object,
-            mask);
+            eventLoop->fired[i].fd = event[i].portev_object;
+            eventLoop->fired[i].mask = mask;
 
-    state->pending_fd = event.portev_object;
-    state->pending_mask = (uintptr_t)event.portev_user;
+            if (evport_debug)
+                fprintf(stderr, "aeApiPoll: fd %d mask 0x%x\n",
+                    (int)event[i].portev_object, mask);
+
+            state->pending_fds[i] = event[i].portev_object;
+            state->pending_masks[i] = (uintptr_t)event[i].portev_user;
+    }
 
-    return 1;
+    return nevents;
 }
 
 static char *aeApiName(void) {