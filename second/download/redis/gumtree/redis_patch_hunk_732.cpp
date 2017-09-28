         /* We know for sure there is a whole line since newline != NULL,
          * so go ahead and find out the multi bulk length. */
         serverAssertWithInfo(c,NULL,c->querybuf[0] == '*');
         ok = string2ll(c->querybuf+1,newline-(c->querybuf+1),&ll);
         if (!ok || ll > 1024*1024) {
             addReplyError(c,"Protocol error: invalid multibulk length");
-            setProtocolError(c,pos);
+            setProtocolError("invalid mbulk count",c,pos);
             return C_ERR;
         }
 
         pos = (newline-c->querybuf)+2;
         if (ll <= 0) {
             sdsrange(c->querybuf,pos,-1);
