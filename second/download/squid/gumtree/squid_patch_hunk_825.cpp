             hist->count(c);
 }
 
 void
 httpHdrCcStatDumper(StoreEntry * sentry, int idx, double val, double size, int count)
 {
-    extern const HttpHeaderStat *dump_stat;	/* argh! */
+    extern const HttpHeaderStat *dump_stat; /* argh! */
     const int id = (int) val;
     const int valid_id = id >= 0 && id < CC_ENUM_END;
     const char *name = valid_id ? CcAttrs[id].name : "INVALID";
 
     if (count || valid_id)
         storeAppendPrintf(sentry, "%2d\t %-20s\t %5d\t %6.2f\n",
