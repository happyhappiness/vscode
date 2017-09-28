         /* "append" is an argument, so always an sds */
         append = c->argv[2];
         totlen = stringObjectLen(o)+sdslen(append->ptr);
         if (checkStringLength(c,totlen) != REDIS_OK)
             return;
 
-        /* If the object is shared or encoded, we have to make a copy */
-        if (o->refcount != 1 || o->encoding != REDIS_ENCODING_RAW) {
-            robj *decoded = getDecodedObject(o);
-            o = createStringObject(decoded->ptr, sdslen(decoded->ptr));
-            decrRefCount(decoded);
-            dbOverwrite(c->db,c->argv[1],o);
-        }
-
         /* Append the value */
+        o = dbUnshareStringValue(c->db,c->argv[1],o);
         o->ptr = sdscatlen(o->ptr,append->ptr,sdslen(append->ptr));
         totlen = sdslen(o->ptr);
     }
     signalModifiedKey(c->db,c->argv[1]);
     notifyKeyspaceEvent(REDIS_NOTIFY_STRING,"append",c->argv[1],c->db->id);
     server.dirty++;
