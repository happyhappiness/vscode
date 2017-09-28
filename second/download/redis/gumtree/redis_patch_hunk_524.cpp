 
             if (c->querybuf[pos] != '$') {
                 addReplyErrorFormat(c,
                     "Protocol error: expected '$', got '%c'",
                     c->querybuf[pos]);
                 setProtocolError(c,pos);
-                return REDIS_ERR;
+                return C_ERR;
             }
 
             ok = string2ll(c->querybuf+pos+1,newline-(c->querybuf+pos+1),&ll);
             if (!ok || ll < 0 || ll > 512*1024*1024) {
                 addReplyError(c,"Protocol error: invalid bulk length");
                 setProtocolError(c,pos);
-                return REDIS_ERR;
+                return C_ERR;
             }
 
             pos += newline-(c->querybuf+pos)+2;
-            if (ll >= REDIS_MBULK_BIG_ARG) {
+            if (ll >= PROTO_MBULK_BIG_ARG) {
                 size_t qblen;
 
                 /* If we are going to read a large object from network
                  * try to make it likely that it will start at c->querybuf
                  * boundary so that we can optimize object creation
                  * avoiding a large copy of data. */
