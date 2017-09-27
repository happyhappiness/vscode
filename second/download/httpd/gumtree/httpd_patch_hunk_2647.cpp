     char msgbuf[100];
     int cur;
 
     switch(ctx->ees) {
     case EES_LIMIT:
         rv = 0;
-        msg = "xlate filter - a built-in restriction was encountered";
+        msg = APLOGNO(02193) "xlate filter - a built-in restriction was encountered";
         break;
     case EES_BAD_INPUT:
         rv = 0;
-        msg = "xlate filter - an input character was invalid";
+        msg = APLOGNO(02194) "xlate filter - an input character was invalid";
         break;
     case EES_BUCKET_READ:
         rv = 0;
-        msg = "xlate filter - bucket read routine failed";
+        msg = APLOGNO(02195) "xlate filter - bucket read routine failed";
         break;
     case EES_INCOMPLETE_CHAR:
         rv = 0;
-        strcpy(msgbuf, "xlate filter - incomplete char at end of input - ");
+        strcpy(msgbuf, APLOGNO(02196) "xlate filter - incomplete char at end of input - ");
         cur = 0;
         while ((apr_size_t)cur < ctx->saved) {
             apr_snprintf(msgbuf + strlen(msgbuf), sizeof(msgbuf) - strlen(msgbuf),
                          "%02X", (unsigned)ctx->buf[cur]);
             ++cur;
         }
         msg = msgbuf;
         break;
     case EES_DOWNSTREAM:
-        msg = "xlate filter - an error occurred in a lower filter";
+        msg = APLOGNO(02197) "xlate filter - an error occurred in a lower filter";
         break;
     default:
-        msg = "xlate filter - returning error";
+        msg = APLOGNO(02198) "xlate filter - returning error";
     }
-    ap_log_rerror(APLOG_MARK, APLOG_ERR, rv, f->r,
-                  "%s", msg);
+    ap_log_rerror(APLOG_MARK, APLOG_ERR, rv, f->r, "%s", msg);
 }
 
 /* chk_filter_chain() is called once per filter instance; it tries to
  * determine if the current filter instance should be disabled because
  * its translation is incompatible with the translation of an existing
  * instance of the translate filter
