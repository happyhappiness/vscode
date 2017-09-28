     char buf[SDS_LLSTR_SIZE];
     int len = sdsll2str(buf,value);
 
     return sdsnewlen(buf,len);
 }
 
-/* Like sdscatpritf() but gets va_list instead of being variadic. */
+/* Like sdscatprintf() but gets va_list instead of being variadic. */
 sds sdscatvprintf(sds s, const char *fmt, va_list ap) {
     va_list cpy;
     char staticbuf[1024], *buf = staticbuf, *t;
     size_t buflen = strlen(fmt)*2;
 
     /* We try to start using a static buffer for speed.
