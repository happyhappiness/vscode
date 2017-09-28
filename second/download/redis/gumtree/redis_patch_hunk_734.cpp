                 break;
 
             if (c->querybuf[pos] != '$') {
                 addReplyErrorFormat(c,
                     "Protocol error: expected '$', got '%c'",
                     c->querybuf[pos]);
-                setProtocolError(c,pos);
+                setProtocolError("expected $ but got something else",c,pos);
                 return C_ERR;
             }
 
             ok = string2ll(c->querybuf+pos+1,newline-(c->querybuf+pos+1),&ll);
             if (!ok || ll < 0 || ll > 512*1024*1024) {
                 addReplyError(c,"Protocol error: invalid bulk length");
-                setProtocolError(c,pos);
+                setProtocolError("invalid bulk length",c,pos);
                 return C_ERR;
             }
 
             pos += newline-(c->querybuf+pos)+2;
             if (ll >= PROTO_MBULK_BIG_ARG) {
                 size_t qblen;
