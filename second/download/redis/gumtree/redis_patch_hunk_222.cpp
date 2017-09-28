         out = sdscatprintf(out,"%lld",r->integer);
     break;
     case REDIS_REPLY_STRING:
         out = sdscatrepr(out,r->str,r->len);
     break;
     case REDIS_REPLY_NIL:
-        out = sdscat(out,"NIL\n");
+        out = sdscat(out,"NIL");
     break;
     case REDIS_REPLY_ARRAY:
         for (i = 0; i < r->elements; i++) {
             sds tmp = cliFormatReplyCSV(r->element[i]);
             out = sdscatlen(out,tmp,sdslen(tmp));
             if (i != r->elements-1) out = sdscat(out,",");
