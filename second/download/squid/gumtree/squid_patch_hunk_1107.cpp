     }
 
     return (mask != 0);
 }
 
 void
-HttpHdrCc::packInto(Packer * p) const
+HttpHdrCc::packInto(Packable * p) const
 {
     // optimization: if the mask is empty do nothing
     if (mask==0)
         return;
 
-    http_hdr_cc_type flag;
+    HttpHdrCcType flag;
     int pcount = 0;
     assert(p);
 
-    for (flag = CC_PUBLIC; flag < CC_ENUM_END; ++flag) {
-        if (isSet(flag) && flag != CC_OTHER) {
+    for (flag = HttpHdrCcType::CC_PUBLIC; flag < HttpHdrCcType::CC_ENUM_END; ++flag) {
+        if (isSet(flag) && flag != HttpHdrCcType::CC_OTHER) {
 
             /* print option name for all options */
-            packerPrintf(p, (pcount ? ", %s": "%s") , CcAttrs[flag].name);
+            p->appendf((pcount ? ", %s": "%s") , CcAttrs[flag].name);
 
             /* for all options having values, "=value" after the name */
             switch (flag) {
-            case CC_BADHDR:
+            case HttpHdrCcType::CC_PUBLIC:
                 break;
-            case CC_PUBLIC:
-                break;
-            case CC_PRIVATE:
+            case HttpHdrCcType::CC_PRIVATE:
                 if (private_.size())
-                    packerPrintf(p, "=\"" SQUIDSTRINGPH "\"", SQUIDSTRINGPRINT(private_));
+                    p->appendf("=\"" SQUIDSTRINGPH "\"", SQUIDSTRINGPRINT(private_));
                 break;
 
-            case CC_NO_CACHE:
-                if (noCache().size())
-                    packerPrintf(p, "=\"" SQUIDSTRINGPH "\"", SQUIDSTRINGPRINT(noCache()));
+            case HttpHdrCcType::CC_NO_CACHE:
+                if (no_cache.size())
+                    p->appendf("=\"" SQUIDSTRINGPH "\"", SQUIDSTRINGPRINT(no_cache));
                 break;
-            case CC_NO_STORE:
+            case HttpHdrCcType::CC_NO_STORE:
                 break;
-            case CC_NO_TRANSFORM:
+            case HttpHdrCcType::CC_NO_TRANSFORM:
                 break;
-            case CC_MUST_REVALIDATE:
+            case HttpHdrCcType::CC_MUST_REVALIDATE:
                 break;
-            case CC_PROXY_REVALIDATE:
+            case HttpHdrCcType::CC_PROXY_REVALIDATE:
                 break;
-            case CC_MAX_AGE:
-                packerPrintf(p, "=%d", (int) maxAge());
+            case HttpHdrCcType::CC_MAX_AGE:
+                p->appendf("=%d", max_age);
                 break;
-            case CC_S_MAXAGE:
-                packerPrintf(p, "=%d", (int) sMaxAge());
+            case HttpHdrCcType::CC_S_MAXAGE:
+                p->appendf("=%d", s_maxage);
                 break;
-            case CC_MAX_STALE:
+            case HttpHdrCcType::CC_MAX_STALE:
                 /* max-stale's value is optional.
                   If we didn't receive it, don't send it */
-                if (maxStale()!=MAX_STALE_ANY)
-                    packerPrintf(p, "=%d", (int) maxStale());
+                if (max_stale != MAX_STALE_ANY)
+                    p->appendf("=%d", max_stale);
+                break;
+            case HttpHdrCcType::CC_MIN_FRESH:
+                p->appendf("=%d", min_fresh);
                 break;
-            case CC_MIN_FRESH:
-                packerPrintf(p, "=%d", (int) minFresh());
+            case HttpHdrCcType::CC_ONLY_IF_CACHED:
                 break;
-            case CC_ONLY_IF_CACHED:
+            case HttpHdrCcType::CC_STALE_IF_ERROR:
+                p->appendf("=%d", stale_if_error);
                 break;
-            case CC_STALE_IF_ERROR:
-                packerPrintf(p, "=%d", staleIfError());
+            case HttpHdrCcType::CC_IMMUTABLE:
                 break;
-            case CC_OTHER:
-            case CC_ENUM_END:
+            case HttpHdrCcType::CC_OTHER:
+            case HttpHdrCcType::CC_ENUM_END:
                 // done below after the loop
                 break;
             }
 
             ++pcount;
         }
     }
 
     if (other.size() != 0)
-        packerPrintf(p, (pcount ? ", " SQUIDSTRINGPH : SQUIDSTRINGPH),
-                     SQUIDSTRINGPRINT(other));
+        p->appendf((pcount ? ", " SQUIDSTRINGPH : SQUIDSTRINGPH), SQUIDSTRINGPRINT(other));
 }
 
 void
 httpHdrCcUpdateStats(const HttpHdrCc * cc, StatHist * hist)
 {
-    http_hdr_cc_type c;
     assert(cc);
 
-    for (c = CC_PUBLIC; c < CC_ENUM_END; ++c)
+    for (HttpHdrCcType c = HttpHdrCcType::CC_PUBLIC; c < HttpHdrCcType::CC_ENUM_END; ++c)
         if (cc->isSet(c))
             hist->count(c);
 }
 
 void
-httpHdrCcStatDumper(StoreEntry * sentry, int idx, double val, double size, int count)
+httpHdrCcStatDumper(StoreEntry * sentry, int, double val, double, int count)
 {
     extern const HttpHeaderStat *dump_stat; /* argh! */
-    const int id = (int) val;
-    const int valid_id = id >= 0 && id < CC_ENUM_END;
+    const int id = static_cast<int>(val);
+    const bool valid_id = id >= 0 && id < static_cast<int>(HttpHdrCcType::CC_ENUM_END);
     const char *name = valid_id ? CcAttrs[id].name : "INVALID";
 
     if (count || valid_id)
         storeAppendPrintf(sentry, "%2d\t %-20s\t %5d\t %6.2f\n",
                           id, name, count, xdiv(count, dump_stat->ccParsedCount));
 }
 
+std::ostream &
+operator<< (std::ostream &s, HttpHdrCcType c)
+{
+    const unsigned char ic = static_cast<int>(c);
+    if (c < HttpHdrCcType::CC_ENUM_END)
+        s << CcAttrs[ic].name << '[' << ic << ']' ;
+    else
+        s << "*invalid hdrcc* [" << ic << ']';
+    return s;
+}
+
 #if !_USE_INLINE_
 #include "HttpHdrCc.cci"
 #endif
 
