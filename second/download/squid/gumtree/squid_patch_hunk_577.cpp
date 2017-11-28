     c->callback_data = cbdataReference(callback_data);
 
     for (C = &state->clients; *C; C = &(*C)->next);
     *C = c;
 }
 
-CBDATA_TYPE(IdentStateData);
-
-/**** PUBLIC FUNCTIONS ****/
-
 /*
  * start a TCP connection to the peer host on port 113
  */
 void
 Ident::Start(const Comm::ConnectionPointer &conn, IDCB * callback, void *data)
 {
     IdentStateData *state;
     char key1[IDENT_KEY_SZ];
     char key2[IDENT_KEY_SZ];
     char key[IDENT_KEY_SZ];
 
-    conn->local.ToURL(key1, IDENT_KEY_SZ);
-    conn->remote.ToURL(key2, IDENT_KEY_SZ);
+    conn->local.toUrl(key1, IDENT_KEY_SZ);
+    conn->remote.toUrl(key2, IDENT_KEY_SZ);
     snprintf(key, IDENT_KEY_SZ, "%s,%s", key1, key2);
 
     if (!ident_hash) {
         Init();
     }
     if ((state = (IdentStateData *)hash_lookup(ident_hash, key)) != NULL) {
         ClientAdd(state, callback, data);
         return;
     }
 
-    CBDATA_INIT_TYPE(IdentStateData);
-    state = cbdataAlloc(IdentStateData);
+    state = new IdentStateData;
     state->hash.key = xstrdup(key);
 
     // copy the conn details. We dont want the original FD to be re-used by IDENT.
     state->conn = conn->copyDetails();
     // NP: use random port for secure outbound to IDENT_PORT
-    state->conn->local.SetPort(0);
-    state->conn->remote.SetPort(IDENT_PORT);
+    state->conn->local.port(0);
+    state->conn->remote.port(IDENT_PORT);
 
     // build our query from the original connection details
     state->queryMsg.init();
-    state->queryMsg.Printf("%d, %d\r\n", conn->remote.GetPort(), conn->local.GetPort());
+    state->queryMsg.Printf("%d, %d\r\n", conn->remote.port(), conn->local.port());
 
     ClientAdd(state, callback, data);
     hash_join(ident_hash, &state->hash);
 
     AsyncCall::Pointer call = commCbCall(30,3, "Ident::ConnectDone", CommConnectCbPtrFun(Ident::ConnectDone, state));
     AsyncJob::Start(new Comm::ConnOpener(state->conn, call, Ident::TheConfig.timeout));
