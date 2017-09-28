         zfree(tokens);
         *count = 0;
         return NULL;
     }
 }
 
+/* Free the result returned by sdssplitlen(), or do nothing if 'tokens' is NULL. */
 void sdsfreesplitres(sds *tokens, int count) {
     if (!tokens) return;
     while(count--)
         sdsfree(tokens[count]);
     zfree(tokens);
 }
 
+/* Create an sds string from a long long value. It is much faster than:
+ *
+ * sdscatprintf(sdsempty(),"%lld\n", value);
+ */
 sds sdsfromlonglong(long long value) {
     char buf[32], *p;
     unsigned long long v;
 
     v = (value < 0) ? -value : value;
     p = buf+31; /* point to the last character */
