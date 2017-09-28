     /* Start parsing all the scores, we need to emit any syntax error
      * before executing additions to the sorted set, as the command should
      * either execute fully or nothing at all. */
     scores = zmalloc(sizeof(double)*elements);
     for (j = 0; j < elements; j++) {
         if (getDoubleFromObjectOrReply(c,c->argv[scoreidx+j*2],&scores[j],NULL)
-            != REDIS_OK) goto cleanup;
+            != C_OK) goto cleanup;
     }
 
     /* Lookup the key and create the sorted set if does not exist. */
     zobj = lookupKeyWrite(c->db,key);
     if (zobj == NULL) {
         if (xx) goto reply_to_client; /* No key + XX option: nothing to do. */
