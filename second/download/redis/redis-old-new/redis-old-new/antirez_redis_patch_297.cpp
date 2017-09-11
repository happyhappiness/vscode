@@ -4604,9 +4604,9 @@ void migrateCommand(client *c) {
     long timeout;
     long dbid;
     long long ttl, expireat;
-    robj **ov = zmalloc(sizeof(robj*)); /* Objects to migrate. */
-    robj **kv = zmalloc(sizeof(robj*)); /* Key names. */
-    robj **newargv = NULL;
+    robj **ov = NULL; /* Objects to migrate. */
+    robj **kv = NULL; /* Key names. */
+    robj **newargv = NULL; /* Used to rewrite the command as DEL ... keys ... */
     rio cmd, payload;
     int may_retry = 1;
     int write_error = 0;
@@ -4631,13 +4631,10 @@ void migrateCommand(client *c) {
                 addReplyError(c,
                     "When using MIGRATE KEYS option, the key argument"
                     " must be set to the empty string");
-                zfree(ov); zfree(kv);
                 return;
             }
             first_key = j+1;
             num_keys = c->argc - j - 1;
-            ov = zrealloc(ov,sizeof(robj*)*num_keys);
-            kv = zrealloc(kv,sizeof(robj*)*num_keys);
             break; /* All the remaining args are keys. */
         } else {
             addReply(c,shared.syntaxerr);
@@ -4649,7 +4646,6 @@ void migrateCommand(client *c) {
     if (getLongFromObjectOrReply(c,c->argv[5],&timeout,NULL) != C_OK ||
         getLongFromObjectOrReply(c,c->argv[4],&dbid,NULL) != C_OK)
     {
-        zfree(ov); zfree(kv);
         return;
     }
     if (timeout <= 0) timeout = 1000;
@@ -4659,7 +4655,10 @@ void migrateCommand(client *c) {
      * the caller there was nothing to migrate. We don't return an error in
      * this case, since often this is due to a normal condition like the key
      * expiring in the meantime. */
+    ov = zrealloc(ov,sizeof(robj*)*num_keys);
+    kv = zrealloc(kv,sizeof(robj*)*num_keys);
     int oi = 0;
+
     for (j = 0; j < num_keys; j++) {
         if ((ov[oi] = lookupKeyRead(c->db,c->argv[first_key+j])) != NULL) {
             kv[oi] = c->argv[first_key+j];
@@ -4809,7 +4808,8 @@ void migrateCommand(client *c) {
     }
 
     /* If we are here and a socket error happened, we don't want to retry.
-     * Just signal the problem to the client. */
+     * Just signal the problem to the client, but only do it if we don't
+     * already queued a different error reported by the destination server. */
     if (!error_from_target && socket_error) {
         may_retry = 0;
         goto socket_err;
@@ -4826,6 +4826,7 @@ void migrateCommand(client *c) {
 
     sdsfree(cmd.io.buffer.ptr);
     zfree(ov); zfree(kv); zfree(newargv);
+    if (socket_error) migrateCloseSocket(c->argv[1],c->argv[2]);
     return;
 
 /* On socket errors we try to close the cached socket and try again.