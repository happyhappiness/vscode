@@ -5,11 +5,11 @@
  *                            | (__| |_| |  _ <| |___
  *                             \___|\___/|_| \_\_____|
  *
- * Copyright (C) 1998 - 2015, Daniel Stenberg, <daniel@haxx.se>, et al.
+ * Copyright (C) 1998 - 2016, Daniel Stenberg, <daniel@haxx.se>, et al.
  *
  * This software is licensed as described in the file COPYING, which
  * you should have received as part of this distribution. The terms
- * are also available at http://curl.haxx.se/docs/copyright.html.
+ * are also available at https://curl.haxx.se/docs/copyright.html.
  *
  * You may opt to use, copy, modify, merge, publish, distribute and/or sell
  * copies of the Software, and permit persons to whom the Software is
@@ -42,9 +42,9 @@
 #include "multihandle.h"
 #include "pipeline.h"
 #include "sigpipe.h"
+/* The last 3 #include files should be in this order */
 #include "curl_printf.h"
 #include "curl_memory.h"
-/* The last #include file should be: */
 #include "memdebug.h"
 
 /*
@@ -61,15 +61,15 @@
 #define CURL_MULTI_HANDLE 0x000bab1e
 
 #define GOOD_MULTI_HANDLE(x) \
-  ((x) && (((struct Curl_multi *)(x))->type == CURL_MULTI_HANDLE))
+  ((x) && (x)->type == CURL_MULTI_HANDLE)
 
 static void singlesocket(struct Curl_multi *multi,
-                         struct SessionHandle *data);
+                         struct Curl_easy *data);
 static int update_timer(struct Curl_multi *multi);
 
 static CURLMcode add_next_timeout(struct timeval now,
                                   struct Curl_multi *multi,
-                                  struct SessionHandle *d);
+                                  struct Curl_easy *d);
 static CURLMcode multi_timeout(struct Curl_multi *multi,
                                long *timeout_ms);
 
@@ -99,14 +99,23 @@ static const char * const statename[]={
 
 static void multi_freetimeout(void *a, void *b);
 
+/* function pointer called once when switching TO a state */
+typedef void (*init_multistate_func)(struct Curl_easy *data);
+
 /* always use this function to change state, to make debugging easier */
-static void mstate(struct SessionHandle *data, CURLMstate state
+static void mstate(struct Curl_easy *data, CURLMstate state
 #ifdef DEBUGBUILD
                    , int lineno
 #endif
 )
 {
   CURLMstate oldstate = data->mstate;
+  static const init_multistate_func finit[CURLM_STATE_LAST] = {
+    NULL,
+    NULL,
+    Curl_init_CONNECT, /* CONNECT */
+    /* the rest is NULL too */
+  };
 
 #if defined(DEBUGBUILD) && defined(CURL_DISABLE_VERBOSE_STRINGS)
   (void) lineno;
@@ -127,7 +136,7 @@ static void mstate(struct SessionHandle *data, CURLMstate state
       connection_id = data->easy_conn->connection_id;
 
     infof(data,
-          "STATE: %s => %s handle %p; line %d (connection #%ld) \n",
+          "STATE: %s => %s handle %p; line %d (connection #%ld)\n",
           statename[oldstate], statename[data->mstate],
           (void *)data, lineno, connection_id);
   }
@@ -136,6 +145,10 @@ static void mstate(struct SessionHandle *data, CURLMstate state
   if(state == CURLM_STATE_COMPLETED)
     /* changing to COMPLETED means there's one less easy handle 'alive' */
     data->multi->num_alive--;
+
+  /* if this state has an init-function, run it */
+  if(finit[state])
+    finit[state](data);
 }
 
 #ifndef DEBUGBUILD
@@ -149,7 +162,7 @@ static void mstate(struct SessionHandle *data, CURLMstate state
  */
 
 struct Curl_sh_entry {
-  struct SessionHandle *easy;
+  struct Curl_easy *easy;
   int action;  /* what action READ/WRITE this socket waits for */
   curl_socket_t socket; /* mainly to ease debugging */
   void *socketp; /* settable by users with curl_multi_assign() */
@@ -159,13 +172,22 @@ struct Curl_sh_entry {
 #define SH_READ  1
 #define SH_WRITE 2
 
+/* look up a given socket in the socket hash, skip invalid sockets */
+static struct Curl_sh_entry *sh_getentry(struct curl_hash *sh,
+                                         curl_socket_t s)
+{
+  if(s != CURL_SOCKET_BAD)
+    /* only look for proper sockets */
+    return Curl_hash_pick(sh, (char *)&s, sizeof(curl_socket_t));
+  return NULL;
+}
+
 /* make sure this socket is present in the hash for this handle */
 static struct Curl_sh_entry *sh_addentry(struct curl_hash *sh,
                                          curl_socket_t s,
-                                         struct SessionHandle *data)
+                                         struct Curl_easy *data)
 {
-  struct Curl_sh_entry *there =
-    Curl_hash_pick(sh, (char *)&s, sizeof(curl_socket_t));
+  struct Curl_sh_entry *there = sh_getentry(sh, s);
   struct Curl_sh_entry *check;
 
   if(there)
@@ -193,15 +215,9 @@ static struct Curl_sh_entry *sh_addentry(struct curl_hash *sh,
 /* delete the given socket + handle from the hash */
 static void sh_delentry(struct curl_hash *sh, curl_socket_t s)
 {
-  struct Curl_sh_entry *there =
-    Curl_hash_pick(sh, (char *)&s, sizeof(curl_socket_t));
-
-  if(there) {
-    /* this socket is in the hash */
-    /* We remove the hash entry. (This'll end up in a call to
-       sh_freeentry().) */
-    Curl_hash_delete(sh, (char *)&s, sizeof(curl_socket_t));
-  }
+  /* We remove the hash entry. This will end up in a call to
+     sh_freeentry(). */
+  Curl_hash_delete(sh, (char *)&s, sizeof(curl_socket_t));
 }
 
 /*
@@ -218,15 +234,15 @@ static size_t fd_key_compare(void *k1, size_t k1_len, void *k2, size_t k2_len)
 {
   (void) k1_len; (void) k2_len;
 
-  return (*((int *) k1)) == (*((int *) k2));
+  return (*((curl_socket_t *) k1)) == (*((curl_socket_t *) k2));
 }
 
 static size_t hash_fd(void *key, size_t key_length, size_t slots_num)
 {
-  int fd = *((int *) key);
+  curl_socket_t fd = *((curl_socket_t *) key);
   (void) key_length;
 
-  return (fd % (int)slots_num);
+  return (fd % slots_num);
 }
 
 /*
@@ -318,7 +334,7 @@ struct Curl_multi *Curl_multi_handle(int hashsize, /* socket hash */
 
   /* -1 means it not set by user, use the default value */
   multi->maxconnects = -1;
-  return (CURLM *) multi;
+  return multi;
 
   error:
 
@@ -334,25 +350,23 @@ struct Curl_multi *Curl_multi_handle(int hashsize, /* socket hash */
   return NULL;
 }
 
-CURLM *curl_multi_init(void)
+struct Curl_multi *curl_multi_init(void)
 {
   return Curl_multi_handle(CURL_SOCKET_HASH_TABLE_SIZE,
                            CURL_CONNECTION_HASH_SIZE);
 }
 
-CURLMcode curl_multi_add_handle(CURLM *multi_handle,
-                                CURL *easy_handle)
+CURLMcode curl_multi_add_handle(struct Curl_multi *multi,
+                                struct Curl_easy *data)
 {
   struct curl_llist *timeoutlist;
-  struct Curl_multi *multi = (struct Curl_multi *)multi_handle;
-  struct SessionHandle *data = (struct SessionHandle *)easy_handle;
 
   /* First, make some basic checks that the CURLM handle is a good handle */
   if(!GOOD_MULTI_HANDLE(multi))
     return CURLM_BAD_HANDLE;
 
   /* Verify that we got a somewhat good easy handle too */
-  if(!GOOD_EASY_HANDLE(easy_handle))
+  if(!GOOD_EASY_HANDLE(data))
     return CURLM_BAD_EASY_HANDLE;
 
   /* Prevent users from adding same easy handle more than once and prevent
@@ -401,14 +415,14 @@ CURLMcode curl_multi_add_handle(CURLM *multi_handle,
   data->state.conn_cache = &multi->conn_cache;
 
   /* This adds the new entry at the 'end' of the doubly-linked circular
-     list of SessionHandle structs to try and maintain a FIFO queue so
+     list of Curl_easy structs to try and maintain a FIFO queue so
      the pipelined requests are in order. */
 
   /* We add this new entry last in the list. */
 
   data->next = NULL; /* end of the line */
   if(multi->easyp) {
-    struct SessionHandle *last = multi->easylp;
+    struct Curl_easy *last = multi->easylp;
     last->next = data;
     data->prev = last;
     multi->easylp = data; /* the new last node */
@@ -419,8 +433,8 @@ CURLMcode curl_multi_add_handle(CURLM *multi_handle,
     multi->easylp = multi->easyp = data; /* both first and last */
   }
 
-  /* make the SessionHandle refer back to this multi handle */
-  data->multi = multi_handle;
+  /* make the Curl_easy refer back to this multi handle */
+  data->multi = multi;
 
   /* Set the timeout for this handle to expire really soon so that it will
      be taken care of even when this handle is added in the midst of operation
@@ -468,12 +482,171 @@ static void debug_print_sock_hash(void *p)
 }
 #endif
 
-CURLMcode curl_multi_remove_handle(CURLM *multi_handle,
-                                   CURL *curl_handle)
+/* Mark the connection as 'idle', or close it if the cache is full.
+   Returns TRUE if the connection is kept, or FALSE if it was closed. */
+static bool
+ConnectionDone(struct Curl_easy *data, struct connectdata *conn)
+{
+  /* data->multi->maxconnects can be negative, deal with it. */
+  size_t maxconnects =
+    (data->multi->maxconnects < 0) ? data->multi->num_easy * 4:
+    data->multi->maxconnects;
+  struct connectdata *conn_candidate = NULL;
+
+  /* Mark the current connection as 'unused' */
+  conn->inuse = FALSE;
+
+  if(maxconnects > 0 &&
+     data->state.conn_cache->num_connections > maxconnects) {
+    infof(data, "Connection cache is full, closing the oldest one.\n");
+
+    conn_candidate = Curl_oldest_idle_connection(data);
+
+    if(conn_candidate) {
+      /* Set the connection's owner correctly */
+      conn_candidate->data = data;
+
+      /* the winner gets the honour of being disconnected */
+      (void)Curl_disconnect(conn_candidate, /* dead_connection */ FALSE);
+    }
+  }
+
+  return (conn_candidate == conn) ? FALSE : TRUE;
+}
+
+static CURLcode multi_done(struct connectdata **connp,
+                          CURLcode status,  /* an error if this is called
+                                               after an error was detected */
+                          bool premature)
 {
-  struct Curl_multi *multi=(struct Curl_multi *)multi_handle;
-  struct SessionHandle *easy = curl_handle;
-  struct SessionHandle *data = easy;
+  CURLcode result;
+  struct connectdata *conn;
+  struct Curl_easy *data;
+
+  DEBUGASSERT(*connp);
+
+  conn = *connp;
+  data = conn->data;
+
+  DEBUGF(infof(data, "multi_done\n"));
+
+  if(data->state.done)
+    /* Stop if multi_done() has already been called */
+    return CURLE_OK;
+
+  Curl_getoff_all_pipelines(data, conn);
+
+  /* Cleanup possible redirect junk */
+  free(data->req.newurl);
+  data->req.newurl = NULL;
+  free(data->req.location);
+  data->req.location = NULL;
+
+  switch(status) {
+  case CURLE_ABORTED_BY_CALLBACK:
+  case CURLE_READ_ERROR:
+  case CURLE_WRITE_ERROR:
+    /* When we're aborted due to a callback return code it basically have to
+       be counted as premature as there is trouble ahead if we don't. We have
+       many callbacks and protocols work differently, we could potentially do
+       this more fine-grained in the future. */
+    premature = TRUE;
+  default:
+    break;
+  }
+
+  /* this calls the protocol-specific function pointer previously set */
+  if(conn->handler->done)
+    result = conn->handler->done(conn, status, premature);
+  else
+    result = status;
+
+  if(CURLE_ABORTED_BY_CALLBACK != result) {
+    /* avoid this if we already aborted by callback to avoid this calling
+       another callback */
+    CURLcode rc = Curl_pgrsDone(conn);
+    if(!result && rc)
+      result = CURLE_ABORTED_BY_CALLBACK;
+  }
+
+  if((!premature &&
+      conn->send_pipe->size + conn->recv_pipe->size != 0 &&
+      !data->set.reuse_forbid &&
+      !conn->bits.close)) {
+    /* Stop if pipeline is not empty and we do not have to close
+       connection. */
+    DEBUGF(infof(data, "Connection still in use, no more multi_done now!\n"));
+    return CURLE_OK;
+  }
+
+  data->state.done = TRUE; /* called just now! */
+  Curl_resolver_cancel(conn);
+
+  if(conn->dns_entry) {
+    Curl_resolv_unlock(data, conn->dns_entry); /* done with this */
+    conn->dns_entry = NULL;
+  }
+
+  /* if the transfer was completed in a paused state there can be buffered
+     data left to write and then kill */
+  free(data->state.tempwrite);
+  data->state.tempwrite = NULL;
+
+  /* if data->set.reuse_forbid is TRUE, it means the libcurl client has
+     forced us to close this connection. This is ignored for requests taking
+     place in a NTLM authentication handshake
+
+     if conn->bits.close is TRUE, it means that the connection should be
+     closed in spite of all our efforts to be nice, due to protocol
+     restrictions in our or the server's end
+
+     if premature is TRUE, it means this connection was said to be DONE before
+     the entire request operation is complete and thus we can't know in what
+     state it is for re-using, so we're forced to close it. In a perfect world
+     we can add code that keep track of if we really must close it here or not,
+     but currently we have no such detail knowledge.
+  */
+
+  if((data->set.reuse_forbid
+#if defined(USE_NTLM)
+      && !(conn->ntlm.state == NTLMSTATE_TYPE2 ||
+           conn->proxyntlm.state == NTLMSTATE_TYPE2)
+#endif
+     ) || conn->bits.close || premature) {
+    CURLcode res2 = Curl_disconnect(conn, premature); /* close connection */
+
+    /* If we had an error already, make sure we return that one. But
+       if we got a new error, return that. */
+    if(!result && res2)
+      result = res2;
+  }
+  else {
+    /* the connection is no longer in use */
+    if(ConnectionDone(data, conn)) {
+      /* remember the most recently used connection */
+      data->state.lastconnect = conn;
+
+      infof(data, "Connection #%ld to host %s left intact\n",
+            conn->connection_id,
+            conn->bits.httpproxy?conn->proxy.dispname:conn->host.dispname);
+    }
+    else
+      data->state.lastconnect = NULL;
+  }
+
+  *connp = NULL; /* to make the caller of this function better detect that
+                    this was either closed or handed over to the connection
+                    cache here, and therefore cannot be used from this point on
+                 */
+  Curl_free_request_state(data);
+
+  return result;
+}
+
+CURLMcode curl_multi_remove_handle(struct Curl_multi *multi,
+                                   struct Curl_easy *data)
+{
+  struct Curl_easy *easy = data;
   bool premature;
   bool easy_owns_conn;
   struct curl_llist_element *e;
@@ -483,7 +656,7 @@ CURLMcode curl_multi_remove_handle(CURLM *multi_handle,
     return CURLM_BAD_HANDLE;
 
   /* Verify that we got a somewhat good easy handle too */
-  if(!GOOD_EASY_HANDLE(curl_handle))
+  if(!GOOD_EASY_HANDLE(data))
     return CURLM_BAD_EASY_HANDLE;
 
   /* Prevent users from trying to remove same easy handle more than once */
@@ -513,8 +686,8 @@ CURLMcode curl_multi_remove_handle(CURLM *multi_handle,
        request but not received its response yet, we need to close
        connection. */
     connclose(data->easy_conn, "Removed with partial response");
-    /* Set connection owner so that Curl_done() closes it.
-       We can safely do this here since connection is killed. */
+    /* Set connection owner so that the DONE function closes it.  We can
+       safely do this here since connection is killed. */
     data->easy_conn->data = easy;
     easy_owns_conn = TRUE;
   }
@@ -524,12 +697,6 @@ CURLMcode curl_multi_remove_handle(CURLM *multi_handle,
      curl_easy_cleanup is called. */
   Curl_expire(data, 0);
 
-  /* destroy the timeout list that is held in the easy handle */
-  if(data->state.timeoutlist) {
-    Curl_llist_destroy(data->state.timeoutlist, NULL);
-    data->state.timeoutlist = NULL;
-  }
-
   if(data->dns.hostcachetype == HCACHE_MULTI) {
     /* stop using the multi handle's DNS cache */
     data->dns.hostcache = NULL;
@@ -538,24 +705,31 @@ CURLMcode curl_multi_remove_handle(CURLM *multi_handle,
 
   if(data->easy_conn) {
 
-    /* we must call Curl_done() here (if we still "own it") so that we don't
-       leave a half-baked one around */
+    /* we must call multi_done() here (if we still own the connection) so that
+       we don't leave a half-baked one around */
     if(easy_owns_conn) {
 
-      /* Curl_done() clears the conn->data field to lose the association
+      /* multi_done() clears the conn->data field to lose the association
          between the easy handle and the connection
 
          Note that this ignores the return code simply because there's
          nothing really useful to do with it anyway! */
-      (void)Curl_done(&data->easy_conn, data->result, premature);
+      (void)multi_done(&data->easy_conn, data->result, premature);
     }
     else
-      /* Clear connection pipelines, if Curl_done above was not called */
+      /* Clear connection pipelines, if multi_done above was not called */
       Curl_getoff_all_pipelines(data, data->easy_conn);
   }
 
   Curl_wildcard_dtor(&data->wildcard);
 
+  /* destroy the timeout list that is held in the easy handle, do this *after*
+     multi_done() as that may actually call Curl_expire that uses this */
+  if(data->state.timeoutlist) {
+    Curl_llist_destroy(data->state.timeoutlist, NULL);
+    data->state.timeoutlist = NULL;
+  }
+
   /* as this was using a shared connection cache we clear the pointer to that
      since we're not part of that multi handle anymore */
   data->state.conn_cache = NULL;
@@ -613,7 +787,7 @@ bool Curl_pipeline_wanted(const struct Curl_multi *multi, int bits)
   return (multi && (multi->pipelining & bits)) ? TRUE : FALSE;
 }
 
-void Curl_multi_handlePipeBreak(struct SessionHandle *data)
+void Curl_multi_handlePipeBreak(struct Curl_easy *data)
 {
   data->easy_conn = NULL;
 }
@@ -666,7 +840,7 @@ static int domore_getsock(struct connectdata *conn,
 }
 
 /* returns bitmapped flags for this handle and its sockets */
-static int multi_getsock(struct SessionHandle *data,
+static int multi_getsock(struct Curl_easy *data,
                          curl_socket_t *socks, /* points to numsocks number
                                                   of sockets */
                          int numsocks)
@@ -732,15 +906,14 @@ static int multi_getsock(struct SessionHandle *data,
 
 }
 
-CURLMcode curl_multi_fdset(CURLM *multi_handle,
+CURLMcode curl_multi_fdset(struct Curl_multi *multi,
                            fd_set *read_fd_set, fd_set *write_fd_set,
                            fd_set *exc_fd_set, int *max_fd)
 {
   /* Scan through all the easy handles to get the file descriptors set.
      Some easy handles may not have connected to the remote host yet,
      and then we must make sure that is done. */
-  struct Curl_multi *multi=(struct Curl_multi *)multi_handle;
-  struct SessionHandle *data;
+  struct Curl_easy *data;
   int this_max_fd=-1;
   curl_socket_t sockbunch[MAX_SOCKSPEREASYHANDLE];
   int bitmap;
@@ -782,21 +955,21 @@ CURLMcode curl_multi_fdset(CURLM *multi_handle,
   return CURLM_OK;
 }
 
-CURLMcode curl_multi_wait(CURLM *multi_handle,
+CURLMcode curl_multi_wait(struct Curl_multi *multi,
                           struct curl_waitfd extra_fds[],
                           unsigned int extra_nfds,
                           int timeout_ms,
                           int *ret)
 {
-  struct Curl_multi *multi=(struct Curl_multi *)multi_handle;
-  struct SessionHandle *data;
+  struct Curl_easy *data;
   curl_socket_t sockbunch[MAX_SOCKSPEREASYHANDLE];
   int bitmap;
   unsigned int i;
   unsigned int nfds = 0;
   unsigned int curlfds;
   struct pollfd *ufds = NULL;
   long timeout_internal;
+  int retcode = 0;
 
   if(!GOOD_MULTI_HANDLE(multi))
     return CURLM_BAD_HANDLE;
@@ -889,18 +1062,20 @@ CURLMcode curl_multi_wait(CURLM *multi_handle,
   }
 
   if(nfds) {
+    int pollrc;
     /* wait... */
-    infof(data, "Curl_poll(%d ds, %d ms)\n", nfds, timeout_ms);
-    i = Curl_poll(ufds, nfds, timeout_ms);
+    pollrc = Curl_poll(ufds, nfds, timeout_ms);
+    DEBUGF(infof(data, "Curl_poll(%d ds, %d ms) == %d\n",
+                 nfds, timeout_ms, pollrc));
 
-    if(i) {
-      unsigned int j;
+    if(pollrc > 0) {
+      retcode = pollrc;
       /* copy revents results from the poll to the curl_multi_wait poll
          struct, the bit values of the actual underlying poll() implementation
          may not be the same as the ones in the public libcurl API! */
-      for(j = 0; j < extra_nfds; j++) {
+      for(i = 0; i < extra_nfds; i++) {
         unsigned short mask = 0;
-        unsigned r = ufds[curlfds + j].revents;
+        unsigned r = ufds[curlfds + i].revents;
 
         if(r & POLLIN)
           mask |= CURL_WAIT_POLLIN;
@@ -909,16 +1084,14 @@ CURLMcode curl_multi_wait(CURLM *multi_handle,
         if(r & POLLPRI)
           mask |= CURL_WAIT_POLLPRI;
 
-        extra_fds[j].revents = mask;
+        extra_fds[i].revents = mask;
       }
     }
   }
-  else
-    i = 0;
 
   free(ufds);
   if(ret)
-    *ret = i;
+    *ret = retcode;
   return CURLM_OK;
 }
 
@@ -951,7 +1124,7 @@ static bool multi_ischanged(struct Curl_multi *multi, bool clear)
 }
 
 CURLMcode Curl_multi_add_perform(struct Curl_multi *multi,
-                                 struct SessionHandle *data,
+                                 struct Curl_easy *data,
                                  struct connectdata *conn)
 {
   CURLMcode rc;
@@ -972,9 +1145,142 @@ CURLMcode Curl_multi_add_perform(struct Curl_multi *multi,
   return rc;
 }
 
+static CURLcode multi_reconnect_request(struct connectdata **connp)
+{
+  CURLcode result = CURLE_OK;
+  struct connectdata *conn = *connp;
+  struct Curl_easy *data = conn->data;
+
+  /* This was a re-use of a connection and we got a write error in the
+   * DO-phase. Then we DISCONNECT this connection and have another attempt to
+   * CONNECT and then DO again! The retry cannot possibly find another
+   * connection to re-use, since we only keep one possible connection for
+   * each.  */
+
+  infof(data, "Re-used connection seems dead, get a new one\n");
+
+  connclose(conn, "Reconnect dead connection"); /* enforce close */
+  result = multi_done(&conn, result, FALSE); /* we are so done with this */
+
+  /* conn may no longer be a good pointer, clear it to avoid mistakes by
+     parent functions */
+  *connp = NULL;
+
+  /*
+   * We need to check for CURLE_SEND_ERROR here as well. This could happen
+   * when the request failed on a FTP connection and thus multi_done() itself
+   * tried to use the connection (again).
+   */
+  if(!result || (CURLE_SEND_ERROR == result)) {
+    bool async;
+    bool protocol_done = TRUE;
+
+    /* Now, redo the connect and get a new connection */
+    result = Curl_connect(data, connp, &async, &protocol_done);
+    if(!result) {
+      /* We have connected or sent away a name resolve query fine */
+
+      conn = *connp; /* setup conn to again point to something nice */
+      if(async) {
+        /* Now, if async is TRUE here, we need to wait for the name
+           to resolve */
+        result = Curl_resolver_wait_resolv(conn, NULL);
+        if(result)
+          return result;
+
+        /* Resolved, continue with the connection */
+        result = Curl_async_resolved(conn, &protocol_done);
+        if(result)
+          return result;
+      }
+    }
+  }
+
+  return result;
+}
+
+/*
+ * do_complete is called when the DO actions are complete.
+ *
+ * We init chunking and trailer bits to their default values here immediately
+ * before receiving any header data for the current request in the pipeline.
+ */
+static void do_complete(struct connectdata *conn)
+{
+  conn->data->req.chunk=FALSE;
+  conn->data->req.maxfd = (conn->sockfd>conn->writesockfd?
+                           conn->sockfd:conn->writesockfd)+1;
+  Curl_pgrsTime(conn->data, TIMER_PRETRANSFER);
+}
+
+static CURLcode multi_do(struct connectdata **connp, bool *done)
+{
+  CURLcode result=CURLE_OK;
+  struct connectdata *conn = *connp;
+  struct Curl_easy *data = conn->data;
+
+  if(conn->handler->do_it) {
+    /* generic protocol-specific function pointer set in curl_connect() */
+    result = conn->handler->do_it(conn, done);
+
+    /* This was formerly done in transfer.c, but we better do it here */
+    if((CURLE_SEND_ERROR == result) && conn->bits.reuse) {
+      /*
+       * If the connection is using an easy handle, call reconnect
+       * to re-establish the connection.  Otherwise, let the multi logic
+       * figure out how to re-establish the connection.
+       */
+      if(!data->multi) {
+        result = multi_reconnect_request(connp);
+
+        if(!result) {
+          /* ... finally back to actually retry the DO phase */
+          conn = *connp; /* re-assign conn since multi_reconnect_request
+                            creates a new connection */
+          result = conn->handler->do_it(conn, done);
+        }
+      }
+      else
+        return result;
+    }
+
+    if(!result && *done)
+      /* do_complete must be called after the protocol-specific DO function */
+      do_complete(conn);
+  }
+  return result;
+}
+
+/*
+ * multi_do_more() is called during the DO_MORE multi state. It is basically a
+ * second stage DO state which (wrongly) was introduced to support FTP's
+ * second connection.
+ *
+ * TODO: A future libcurl should be able to work away this state.
+ *
+ * 'complete' can return 0 for incomplete, 1 for done and -1 for go back to
+ * DOING state there's more work to do!
+ */
+
+static CURLcode multi_do_more(struct connectdata *conn, int *complete)
+{
+  CURLcode result=CURLE_OK;
+
+  *complete = 0;
+
+  if(conn->handler->do_more)
+    result = conn->handler->do_more(conn, complete);
+
+  if(!result && (*complete == 1))
+    /* do_complete must be called after the protocol-specific DO function */
+    do_complete(conn);
+
+  return result;
+}
+
 static CURLMcode multi_runsingle(struct Curl_multi *multi,
                                  struct timeval now,
-                                 struct SessionHandle *data)
+                                 struct Curl_easy *data)
 {
   struct Curl_message *msg = NULL;
   bool connected;
@@ -1057,7 +1363,7 @@ static CURLMcode multi_runsingle(struct Curl_multi *multi,
             failf(data, "Operation timed out after %ld milliseconds with %"
                   CURL_FORMAT_CURL_OFF_T " out of %"
                   CURL_FORMAT_CURL_OFF_T " bytes received",
-                  Curl_tvdiff(k->now, data->progress.t_startsingle),
+                  Curl_tvdiff(now, data->progress.t_startsingle),
                   k->bytecount, k->size);
           }
           else {
@@ -1074,7 +1380,7 @@ static CURLMcode multi_runsingle(struct Curl_multi *multi,
           disconnect_conn = TRUE;
         }
         result = CURLE_OPERATION_TIMEDOUT;
-        (void)Curl_done(&data->easy_conn, result, TRUE);
+        (void)multi_done(&data->easy_conn, result, TRUE);
         /* Skip the statemachine and go directly to error handling section. */
         goto statemachine_end;
       }
@@ -1152,17 +1458,25 @@ static CURLMcode multi_runsingle(struct Curl_multi *multi,
     {
       struct Curl_dns_entry *dns = NULL;
       struct connectdata *conn = data->easy_conn;
+      const char *hostname;
+
+      if(conn->bits.proxy)
+        hostname = conn->proxy.name;
+      else if(conn->bits.conn_to_host)
+        hostname = conn->conn_to_host.name;
+      else
+        hostname = conn->host.name;
 
       /* check if we have the name resolved by now */
-      dns = Curl_fetch_addr(conn, conn->host.name, (int)conn->port);
+      dns = Curl_fetch_addr(conn, hostname, (int)conn->port);
 
       if(dns) {
 #ifdef CURLRES_ASYNCH
         conn->async.dns = dns;
         conn->async.done = TRUE;
 #endif
         result = CURLE_OK;
-        infof(data, "Hostname was found in DNS cache\n");
+        infof(data, "Hostname '%s' was found in DNS cache\n", hostname);
       }
 
       if(!dns)
@@ -1215,17 +1529,19 @@ static CURLMcode multi_runsingle(struct Curl_multi *multi,
       /* this is HTTP-specific, but sending CONNECT to a proxy is HTTP... */
       result = Curl_http_connect(data->easy_conn, &protocol_connect);
 
-      rc = CURLM_CALL_MULTI_PERFORM;
       if(data->easy_conn->bits.proxy_connect_closed) {
+        rc = CURLM_CALL_MULTI_PERFORM;
         /* connect back to proxy again */
         result = CURLE_OK;
-        Curl_done(&data->easy_conn, CURLE_OK, FALSE);
+        multi_done(&data->easy_conn, CURLE_OK, FALSE);
         multistate(data, CURLM_STATE_CONNECT);
       }
       else if(!result) {
-        if(data->easy_conn->tunnel_state[FIRSTSOCKET] == TUNNEL_COMPLETE)
+        if(data->easy_conn->tunnel_state[FIRSTSOCKET] == TUNNEL_COMPLETE) {
+          rc = CURLM_CALL_MULTI_PERFORM;
           /* initiate protocol connect phase */
           multistate(data, CURLM_STATE_SENDPROTOCONNECT);
+        }
       }
       break;
 #endif
@@ -1261,7 +1577,7 @@ static CURLMcode multi_runsingle(struct Curl_multi *multi,
       else if(result) {
         /* failure detected */
         Curl_posttransfer(data);
-        Curl_done(&data->easy_conn, result, TRUE);
+        multi_done(&data->easy_conn, result, TRUE);
         disconnect_conn = TRUE;
       }
       break;
@@ -1278,7 +1594,7 @@ static CURLMcode multi_runsingle(struct Curl_multi *multi,
       else if(result) {
         /* failure detected */
         Curl_posttransfer(data);
-        Curl_done(&data->easy_conn, result, TRUE);
+        multi_done(&data->easy_conn, result, TRUE);
         disconnect_conn = TRUE;
       }
       break;
@@ -1302,9 +1618,9 @@ static CURLMcode multi_runsingle(struct Curl_multi *multi,
       }
       else {
         /* Perform the protocol's DO action */
-        result = Curl_do(&data->easy_conn, &dophase_done);
+        result = multi_do(&data->easy_conn, &dophase_done);
 
-        /* When Curl_do() returns failure, data->easy_conn might be NULL! */
+        /* When multi_do() returns failure, data->easy_conn might be NULL! */
 
         if(!result) {
           if(!dophase_done) {
@@ -1313,7 +1629,7 @@ static CURLMcode multi_runsingle(struct Curl_multi *multi,
               struct WildcardData *wc = &data->wildcard;
               if(wc->state == CURLWC_DONE || wc->state == CURLWC_SKIP) {
                 /* skip some states if it is important */
-                Curl_done(&data->easy_conn, CURLE_OK, FALSE);
+                multi_done(&data->easy_conn, CURLE_OK, FALSE);
                 multistate(data, CURLM_STATE_DONE);
                 rc = CURLM_CALL_MULTI_PERFORM;
                 break;
@@ -1360,7 +1676,7 @@ static CURLMcode multi_runsingle(struct Curl_multi *multi,
             retry = (newurl)?TRUE:FALSE;
 
           Curl_posttransfer(data);
-          drc = Curl_done(&data->easy_conn, result, FALSE);
+          drc = multi_done(&data->easy_conn, result, FALSE);
 
           /* When set to retry the connection, we must to go back to
            * the CONNECT state */
@@ -1395,7 +1711,7 @@ static CURLMcode multi_runsingle(struct Curl_multi *multi,
           /* failure detected */
           Curl_posttransfer(data);
           if(data->easy_conn)
-            Curl_done(&data->easy_conn, result, FALSE);
+            multi_done(&data->easy_conn, result, FALSE);
           disconnect_conn = TRUE;
         }
       }
@@ -1417,7 +1733,7 @@ static CURLMcode multi_runsingle(struct Curl_multi *multi,
       else {
         /* failure detected */
         Curl_posttransfer(data);
-        Curl_done(&data->easy_conn, result, FALSE);
+        multi_done(&data->easy_conn, result, FALSE);
         disconnect_conn = TRUE;
       }
       break;
@@ -1426,10 +1742,10 @@ static CURLMcode multi_runsingle(struct Curl_multi *multi,
       /*
        * When we are connected, DO MORE and then go DO_DONE
        */
-      result = Curl_do_more(data->easy_conn, &control);
+      result = multi_do_more(data->easy_conn, &control);
 
       /* No need to remove this handle from the send pipeline here since that
-         is done in Curl_done() */
+         is done in multi_done() */
       if(!result) {
         if(control) {
           /* if positive, advance to DO_DONE
@@ -1446,7 +1762,7 @@ static CURLMcode multi_runsingle(struct Curl_multi *multi,
       else {
         /* failure detected */
         Curl_posttransfer(data);
-        Curl_done(&data->easy_conn, result, FALSE);
+        multi_done(&data->easy_conn, result, FALSE);
         disconnect_conn = TRUE;
       }
       break;
@@ -1484,7 +1800,7 @@ static CURLMcode multi_runsingle(struct Curl_multi *multi,
         result = Curl_speedcheck(data, now);
 
       if(( (data->set.max_send_speed == 0) ||
-           (data->progress.ulspeed < data->set.max_send_speed ))  &&
+           (data->progress.ulspeed < data->set.max_send_speed))  &&
          ( (data->set.max_recv_speed == 0) ||
            (data->progress.dlspeed < data->set.max_recv_speed)))
         multistate(data, CURLM_STATE_PERFORM);
@@ -1566,11 +1882,12 @@ static CURLMcode multi_runsingle(struct Curl_multi *multi,
          * happened in the data connection.
          */
 
-        if(!(data->easy_conn->handler->flags & PROTOPT_DUAL))
+        if(!(data->easy_conn->handler->flags & PROTOPT_DUAL) &&
+           result != CURLE_HTTP2_STREAM)
           connclose(data->easy_conn, "Transfer returned error");
 
         Curl_posttransfer(data);
-        Curl_done(&data->easy_conn, result, FALSE);
+        multi_done(&data->easy_conn, result, FALSE);
       }
       else if(done) {
         followtype follow=FOLLOW_NONE;
@@ -1601,7 +1918,7 @@ static CURLMcode multi_runsingle(struct Curl_multi *multi,
           }
           else
             follow = FOLLOW_RETRY;
-          result = Curl_done(&data->easy_conn, CURLE_OK, FALSE);
+          result = multi_done(&data->easy_conn, CURLE_OK, FALSE);
           if(!result) {
             result = Curl_follow(data, newurl, follow);
             if(!result) {
@@ -1651,14 +1968,14 @@ static CURLMcode multi_runsingle(struct Curl_multi *multi,
         Curl_multi_process_pending_handles(multi);
 
         /* post-transfer command */
-        res = Curl_done(&data->easy_conn, result, FALSE);
+        res = multi_done(&data->easy_conn, result, FALSE);
 
         /* allow a previously set error code take precedence */
         if(!result)
           result = res;
 
         /*
-         * If there are other handles on the pipeline, Curl_done won't set
+         * If there are other handles on the pipeline, multi_done won't set
          * easy_conn to NULL.  In such a case, curl_multi_remove_handle() can
          * access free'd data, if the connection is free'd and the handle
          * removed before we perform the processing in CURLM_STATE_COMPLETED
@@ -1677,7 +1994,7 @@ static CURLMcode multi_runsingle(struct Curl_multi *multi,
       }
 
       /* after we have DONE what we're supposed to do, go COMPLETED, and
-         it doesn't matter what the Curl_done() returned! */
+         it doesn't matter what the multi_done() returned! */
       multistate(data, CURLM_STATE_COMPLETED);
       break;
 
@@ -1779,10 +2096,9 @@ static CURLMcode multi_runsingle(struct Curl_multi *multi,
 }
 
 
-CURLMcode curl_multi_perform(CURLM *multi_handle, int *running_handles)
+CURLMcode curl_multi_perform(struct Curl_multi *multi, int *running_handles)
 {
-  struct Curl_multi *multi=(struct Curl_multi *)multi_handle;
-  struct SessionHandle *data;
+  struct Curl_easy *data;
   CURLMcode returncode=CURLM_OK;
   struct Curl_tree *t;
   struct timeval now = Curl_tvnow();
@@ -1793,27 +2109,12 @@ CURLMcode curl_multi_perform(CURLM *multi_handle, int *running_handles)
   data=multi->easyp;
   while(data) {
     CURLMcode result;
-    struct WildcardData *wc = &data->wildcard;
     SIGPIPE_VARIABLE(pipe_st);
 
-    if(data->set.wildcardmatch) {
-      if(!wc->filelist) {
-        CURLcode ret = Curl_wildcard_init(wc); /* init wildcard structures */
-        if(ret)
-          return CURLM_OUT_OF_MEMORY;
-      }
-    }
-
     sigpipe_ignore(data, &pipe_st);
     result = multi_runsingle(multi, now, data);
     sigpipe_restore(&pipe_st);
 
-    if(data->set.wildcardmatch) {
-      /* destruct wildcard structures if it is needed */
-      if(wc->state == CURLWC_DONE || result)
-        Curl_wildcard_dtor(wc);
-    }
-
     if(result)
       returncode = result;
 
@@ -1856,6 +2157,8 @@ static void close_all_connections(struct Curl_multi *multi)
     conn->data = multi->closure_handle;
 
     sigpipe_ignore(conn->data, &pipe_st);
+    conn->data->easy_conn = NULL; /* clear the easy handle's connection
+                                     pointer */
     /* This will remove the connection from the cache */
     (void)Curl_disconnect(conn, FALSE);
     sigpipe_restore(&pipe_st);
@@ -1864,11 +2167,10 @@ static void close_all_connections(struct Curl_multi *multi)
   }
 }
 
-CURLMcode curl_multi_cleanup(CURLM *multi_handle)
+CURLMcode curl_multi_cleanup(struct Curl_multi *multi)
 {
-  struct Curl_multi *multi=(struct Curl_multi *)multi_handle;
-  struct SessionHandle *data;
-  struct SessionHandle *nextdata;
+  struct Curl_easy *data;
+  struct Curl_easy *nextdata;
 
   if(GOOD_MULTI_HANDLE(multi)) {
     bool restore_pipe = FALSE;
@@ -1939,9 +2241,8 @@ CURLMcode curl_multi_cleanup(CURLM *multi_handle)
  * beyond. The current design is fully O(1).
  */
 
-CURLMsg *curl_multi_info_read(CURLM *multi_handle, int *msgs_in_queue)
+CURLMsg *curl_multi_info_read(struct Curl_multi *multi, int *msgs_in_queue)
 {
-  struct Curl_multi *multi=(struct Curl_multi *)multi_handle;
   struct Curl_message *msg;
 
   *msgs_in_queue = 0; /* default to none */
@@ -1972,15 +2273,14 @@ CURLMsg *curl_multi_info_read(CURLM *multi_handle, int *msgs_in_queue)
  * call the callback accordingly.
  */
 static void singlesocket(struct Curl_multi *multi,
-                         struct SessionHandle *data)
+                         struct Curl_easy *data)
 {
   curl_socket_t socks[MAX_SOCKSPEREASYHANDLE];
   int i;
   struct Curl_sh_entry *entry;
   curl_socket_t s;
   int num;
   unsigned int curraction;
-  bool remove_sock_from_hash;
 
   for(i=0; i< MAX_SOCKSPEREASYHANDLE; i++)
     socks[i] = CURL_SOCKET_BAD;
@@ -2002,7 +2302,7 @@ static void singlesocket(struct Curl_multi *multi,
     s = socks[i];
 
     /* get it from the hash */
-    entry = Curl_hash_pick(&multi->sockhash, (char *)&s, sizeof(s));
+    entry = sh_getentry(&multi->sockhash, s);
 
     if(curraction & GETSOCK_READSOCK(i))
       action |= CURL_POLL_IN;
@@ -2048,57 +2348,50 @@ static void singlesocket(struct Curl_multi *multi,
         break;
       }
     }
-    if(s != CURL_SOCKET_BAD) {
 
+    entry = sh_getentry(&multi->sockhash, s);
+    if(entry) {
       /* this socket has been removed. Tell the app to remove it */
-      remove_sock_from_hash = TRUE;
-
-      entry = Curl_hash_pick(&multi->sockhash, (char *)&s, sizeof(s));
-      if(entry) {
-        /* check if the socket to be removed serves a connection which has
-           other easy-s in a pipeline. In this case the socket should not be
-           removed. */
-        struct connectdata *easy_conn = data->easy_conn;
-        if(easy_conn) {
-          if(easy_conn->recv_pipe && easy_conn->recv_pipe->size > 1) {
-            /* the handle should not be removed from the pipe yet */
-            remove_sock_from_hash = FALSE;
-
-            /* Update the sockhash entry to instead point to the next in line
-               for the recv_pipe, or the first (in case this particular easy
-               isn't already) */
-            if(entry->easy == data) {
-              if(Curl_recvpipe_head(data, easy_conn))
-                entry->easy = easy_conn->recv_pipe->head->next->ptr;
-              else
-                entry->easy = easy_conn->recv_pipe->head->ptr;
-            }
+      bool remove_sock_from_hash = TRUE;
+
+      /* check if the socket to be removed serves a connection which has
+         other easy-s in a pipeline. In this case the socket should not be
+         removed. */
+      struct connectdata *easy_conn = data->easy_conn;
+      if(easy_conn) {
+        if(easy_conn->recv_pipe && easy_conn->recv_pipe->size > 1) {
+          /* the handle should not be removed from the pipe yet */
+          remove_sock_from_hash = FALSE;
+
+          /* Update the sockhash entry to instead point to the next in line
+             for the recv_pipe, or the first (in case this particular easy
+             isn't already) */
+          if(entry->easy == data) {
+            if(Curl_recvpipe_head(data, easy_conn))
+              entry->easy = easy_conn->recv_pipe->head->next->ptr;
+            else
+              entry->easy = easy_conn->recv_pipe->head->ptr;
           }
-          if(easy_conn->send_pipe  && easy_conn->send_pipe->size > 1) {
-            /* the handle should not be removed from the pipe yet */
-            remove_sock_from_hash = FALSE;
-
-            /* Update the sockhash entry to instead point to the next in line
-               for the send_pipe, or the first (in case this particular easy
-               isn't already) */
-            if(entry->easy == data) {
-              if(Curl_sendpipe_head(data, easy_conn))
-                entry->easy = easy_conn->send_pipe->head->next->ptr;
-              else
-                entry->easy = easy_conn->send_pipe->head->ptr;
-            }
+        }
+        if(easy_conn->send_pipe  && easy_conn->send_pipe->size > 1) {
+          /* the handle should not be removed from the pipe yet */
+          remove_sock_from_hash = FALSE;
+
+          /* Update the sockhash entry to instead point to the next in line
+             for the send_pipe, or the first (in case this particular easy
+             isn't already) */
+          if(entry->easy == data) {
+            if(Curl_sendpipe_head(data, easy_conn))
+              entry->easy = easy_conn->send_pipe->head->next->ptr;
+            else
+              entry->easy = easy_conn->send_pipe->head->ptr;
           }
-          /* Don't worry about overwriting recv_pipe head with send_pipe_head,
-             when action will be asked on the socket (see multi_socket()), the
-             head of the correct pipe will be taken according to the
-             action. */
         }
+        /* Don't worry about overwriting recv_pipe head with send_pipe_head,
+           when action will be asked on the socket (see multi_socket()), the
+           head of the correct pipe will be taken according to the
+           action. */
       }
-      else
-        /* just a precaution, this socket really SHOULD be in the hash already
-           but in case it isn't, we don't have to tell the app to remove it
-           either since it never got to know about it */
-        remove_sock_from_hash = FALSE;
 
       if(remove_sock_from_hash) {
         /* in this case 'entry' is always non-NULL */
@@ -2110,9 +2403,8 @@ static void singlesocket(struct Curl_multi *multi,
                            entry->socketp);
         sh_delentry(&multi->sockhash, s);
       }
-
-    }
-  }
+    } /* if sockhash entry existed */
+  } /* for loop over numsocks */
 
   memcpy(data->sockets, socks, num*sizeof(curl_socket_t));
   data->numsocks = num;
@@ -2134,8 +2426,7 @@ void Curl_multi_closed(struct connectdata *conn, curl_socket_t s)
   if(multi) {
     /* this is set if this connection is part of a handle that is added to
        a multi handle, and only then this is necessary */
-    struct Curl_sh_entry *entry =
-      Curl_hash_pick(&multi->sockhash, (char *)&s, sizeof(s));
+    struct Curl_sh_entry *entry = sh_getentry(&multi->sockhash, s);
 
     if(entry) {
       if(multi->socket_cb)
@@ -2154,7 +2445,7 @@ void Curl_multi_closed(struct connectdata *conn, curl_socket_t s)
 /*
  * add_next_timeout()
  *
- * Each SessionHandle has a list of timeouts. The add_next_timeout() is called
+ * Each Curl_easy has a list of timeouts. The add_next_timeout() is called
  * when it has just been removed from the splay tree because the timeout has
  * expired. This function is then to advance in the list to pick the next
  * timeout to use (skip the already expired ones) and add this node back to
@@ -2165,7 +2456,7 @@ void Curl_multi_closed(struct connectdata *conn, curl_socket_t s)
  */
 static CURLMcode add_next_timeout(struct timeval now,
                                   struct Curl_multi *multi,
-                                  struct SessionHandle *d)
+                                  struct Curl_easy *d)
 {
   struct timeval *tv = &d->state.expiretime;
   struct curl_llist *list = d->state.timeoutlist;
@@ -2174,7 +2465,7 @@ static CURLMcode add_next_timeout(struct timeval now,
   /* move over the timeout list for this specific handle and remove all
      timeouts that are now passed tense and store the next pending
      timeout in *tv */
-  for(e = list->head; e; ) {
+  for(e = list->head; e;) {
     struct curl_llist_element *n = e->next;
     long diff = curlx_tvdiff(*(struct timeval *)e->ptr, now);
     if(diff <= 0)
@@ -2213,7 +2504,7 @@ static CURLMcode multi_socket(struct Curl_multi *multi,
                               int *running_handles)
 {
   CURLMcode result = CURLM_OK;
-  struct SessionHandle *data = NULL;
+  struct Curl_easy *data = NULL;
   struct Curl_tree *t;
   struct timeval now = Curl_tvnow();
 
@@ -2236,8 +2527,7 @@ static CURLMcode multi_socket(struct Curl_multi *multi,
   }
   else if(s != CURL_SOCKET_TIMEOUT) {
 
-    struct Curl_sh_entry *entry =
-      Curl_hash_pick(&multi->sockhash, (char *)&s, sizeof(s));
+    struct Curl_sh_entry *entry = sh_getentry(&multi->sockhash, s);
 
     if(!entry)
       /* Unmatched socket, we can't act on it but we ignore this fact.  In
@@ -2342,10 +2632,9 @@ static CURLMcode multi_socket(struct Curl_multi *multi,
 }
 
 #undef curl_multi_setopt
-CURLMcode curl_multi_setopt(CURLM *multi_handle,
+CURLMcode curl_multi_setopt(struct Curl_multi *multi,
                             CURLMoption option, ...)
 {
-  struct Curl_multi *multi=(struct Curl_multi *)multi_handle;
   CURLMcode res = CURLM_OK;
   va_list param;
 
@@ -2413,33 +2702,32 @@ CURLMcode curl_multi_setopt(CURLM *multi_handle,
 /* we define curl_multi_socket() in the public multi.h header */
 #undef curl_multi_socket
 
-CURLMcode curl_multi_socket(CURLM *multi_handle, curl_socket_t s,
+CURLMcode curl_multi_socket(struct Curl_multi *multi, curl_socket_t s,
                             int *running_handles)
 {
-  CURLMcode result = multi_socket((struct Curl_multi *)multi_handle, FALSE, s,
-                                  0, running_handles);
+  CURLMcode result = multi_socket(multi, FALSE, s, 0, running_handles);
   if(CURLM_OK >= result)
-    update_timer((struct Curl_multi *)multi_handle);
+    update_timer(multi);
   return result;
 }
 
-CURLMcode curl_multi_socket_action(CURLM *multi_handle, curl_socket_t s,
+CURLMcode curl_multi_socket_action(struct Curl_multi *multi, curl_socket_t s,
                                    int ev_bitmask, int *running_handles)
 {
-  CURLMcode result = multi_socket((struct Curl_multi *)multi_handle, FALSE, s,
+  CURLMcode result = multi_socket(multi, FALSE, s,
                                   ev_bitmask, running_handles);
   if(CURLM_OK >= result)
-    update_timer((struct Curl_multi *)multi_handle);
+    update_timer(multi);
   return result;
 }
 
-CURLMcode curl_multi_socket_all(CURLM *multi_handle, int *running_handles)
+CURLMcode curl_multi_socket_all(struct Curl_multi *multi, int *running_handles)
 
 {
-  CURLMcode result = multi_socket((struct Curl_multi *)multi_handle,
-                                  TRUE, CURL_SOCKET_BAD, 0, running_handles);
+  CURLMcode result = multi_socket(multi, TRUE, CURL_SOCKET_BAD, 0,
+                                  running_handles);
   if(CURLM_OK >= result)
-    update_timer((struct Curl_multi *)multi_handle);
+    update_timer(multi);
   return result;
 }
 
@@ -2478,11 +2766,9 @@ static CURLMcode multi_timeout(struct Curl_multi *multi,
   return CURLM_OK;
 }
 
-CURLMcode curl_multi_timeout(CURLM *multi_handle,
+CURLMcode curl_multi_timeout(struct Curl_multi *multi,
                              long *timeout_ms)
 {
-  struct Curl_multi *multi=(struct Curl_multi *)multi_handle;
-
   /* First, make some basic checks that the CURLM handle is a good handle */
   if(!GOOD_MULTI_HANDLE(multi))
     return CURLM_BAD_HANDLE;
@@ -2509,7 +2795,7 @@ static int update_timer(struct Curl_multi *multi)
       multi->timer_lastcall = none;
       /* there's no timeout now but there was one previously, tell the app to
          disable it */
-      return multi->timer_cb((CURLM*)multi, -1, multi->timer_userp);
+      return multi->timer_cb(multi, -1, multi->timer_userp);
     }
     return 0;
   }
@@ -2523,7 +2809,7 @@ static int update_timer(struct Curl_multi *multi)
 
   multi->timer_lastcall = multi->timetree->key;
 
-  return multi->timer_cb((CURLM*)multi, timeout_ms, multi->timer_userp);
+  return multi->timer_cb(multi, timeout_ms, multi->timer_userp);
 }
 
 /*
@@ -2595,7 +2881,7 @@ multi_addtimeout(struct curl_llist *timeoutlist,
  *
  * Pass zero to clear all timeout values for this handle.
 */
-void Curl_expire(struct SessionHandle *data, long milli)
+void Curl_expire(struct Curl_easy *data, long milli)
 {
   struct Curl_multi *multi = data->multi;
   struct timeval *nowp = &data->state.expiretime;
@@ -2689,7 +2975,7 @@ void Curl_expire(struct SessionHandle *data, long milli)
  * time-out period to expire.
  *
  */
-void Curl_expire_latest(struct SessionHandle *data, long milli)
+void Curl_expire_latest(struct Curl_easy *data, long milli)
 {
   struct timeval *expire = &data->state.expiretime;
 
@@ -2718,15 +3004,12 @@ void Curl_expire_latest(struct SessionHandle *data, long milli)
   Curl_expire(data, milli);
 }
 
-CURLMcode curl_multi_assign(CURLM *multi_handle,
-                            curl_socket_t s, void *hashp)
+CURLMcode curl_multi_assign(struct Curl_multi *multi, curl_socket_t s,
+                            void *hashp)
 {
   struct Curl_sh_entry *there = NULL;
-  struct Curl_multi *multi = (struct Curl_multi *)multi_handle;
 
-  if(s != CURL_SOCKET_BAD)
-    there = Curl_hash_pick(&multi->sockhash, (char *)&s,
-                           sizeof(curl_socket_t));
+  there = sh_getentry(&multi->sockhash, s);
 
   if(!there)
     return CURLM_BAD_SOCKET;
@@ -2771,7 +3054,7 @@ void Curl_multi_process_pending_handles(struct Curl_multi *multi)
   struct curl_llist_element *e = multi->pending->head;
 
   while(e) {
-    struct SessionHandle *data = e->ptr;
+    struct Curl_easy *data = e->ptr;
     struct curl_llist_element *next = e->next;
 
     if(data->mstate == CURLM_STATE_CONNECT_PEND) {
@@ -2789,10 +3072,9 @@ void Curl_multi_process_pending_handles(struct Curl_multi *multi)
 }
 
 #ifdef DEBUGBUILD
-void Curl_multi_dump(const struct Curl_multi *multi_handle)
+void Curl_multi_dump(struct Curl_multi *multi)
 {
-  struct Curl_multi *multi=(struct Curl_multi *)multi_handle;
-  struct SessionHandle *data;
+  struct Curl_easy *data;
   int i;
   fprintf(stderr, "* Multi status: %d handles, %d alive\n",
           multi->num_easy, multi->num_alive);
@@ -2804,8 +3086,7 @@ void Curl_multi_dump(const struct Curl_multi *multi_handle)
               statename[data->mstate], data->numsocks);
       for(i=0; i < data->numsocks; i++) {
         curl_socket_t s = data->sockets[i];
-        struct Curl_sh_entry *entry =
-          Curl_hash_pick(&multi->sockhash, (char *)&s, sizeof(s));
+        struct Curl_sh_entry *entry = sh_getentry(&multi->sockhash, s);
 
         fprintf(stderr, "%d ", (int)s);
         if(!entry) {