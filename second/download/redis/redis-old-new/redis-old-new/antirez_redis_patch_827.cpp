@@ -1,6 +1,6 @@
-/* SDS (Simple Dynamic Strings), A C dynamic strings library.
+/* SDSLib, A C dynamic strings library
  *
- * Copyright (c) 2006-2014, Salvatore Sanfilippo <antirez at gmail dot com>
+ * Copyright (c) 2006-2010, Salvatore Sanfilippo <antirez at gmail dot com>
  * All rights reserved.
  *
  * Redistribution and use in source and binary forms, with or without
@@ -45,12 +45,12 @@ struct sdshdr {
 };
 
 static inline size_t sdslen(const sds s) {
-    struct sdshdr *sh = (void*)(s-sizeof *sh);
+    struct sdshdr *sh = (void*)(s-(sizeof(struct sdshdr)));
     return sh->len;
 }
 
 static inline size_t sdsavail(const sds s) {
-    struct sdshdr *sh = (void*)(s-sizeof *sh);
+    struct sdshdr *sh = (void*)(s-(sizeof(struct sdshdr)));
     return sh->free;
 }
 
@@ -76,7 +76,8 @@ sds sdscatprintf(sds s, const char *fmt, ...)
 sds sdscatprintf(sds s, const char *fmt, ...);
 #endif
 
-void sdstrim(sds s, const char *cset);
+sds sdscatfmt(sds s, char const *fmt, ...);
+sds sdstrim(sds s, const char *cset);
 void sdsrange(sds s, int start, int end);
 void sdsupdatelen(sds s);
 void sdsclear(sds s);
@@ -89,8 +90,7 @@ sds sdsfromlonglong(long long value);
 sds sdscatrepr(sds s, const char *p, size_t len);
 sds *sdssplitargs(const char *line, int *argc);
 sds sdsmapchars(sds s, const char *from, const char *to, size_t setlen);
-sds sdsjoin(char **argv, int argc, char *sep, size_t seplen);
-sds sdsjoinsds(sds *argv, int argc, const char *sep, size_t seplen);
+sds sdsjoin(char **argv, int argc, char *sep);
 
 /* Low level functions exposed to the user API */
 sds sdsMakeRoomFor(sds s, size_t addlen);