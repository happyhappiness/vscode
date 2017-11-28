  *  You should have received a copy of the GNU General Public License
  *  along with this program; if not, write to the Free Software
  *  Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111, USA.
  *
  */
 
-#include "squid.h"
-#include "Store.h"
+#include "squid-old.h"
+#include "base/StringArea.h"
 #include "HttpHeader.h"
+#include "HttpHeaderStat.h"
+#include "HttpHdrCc.h"
+#include "StatHist.h"
+#include "Store.h"
 
-/* this table is used for parsing cache control header */
-static const HttpHeaderFieldAttrs CcAttrs[CC_ENUM_END] = {
-    {"public", (http_hdr_type)CC_PUBLIC},
-
-    {"private", (http_hdr_type)CC_PRIVATE},
-    {"no-cache", (http_hdr_type)CC_NO_CACHE},
-    {"no-store", (http_hdr_type)CC_NO_STORE},
-    {"no-transform", (http_hdr_type)CC_NO_TRANSFORM},
-    {"must-revalidate", (http_hdr_type)CC_MUST_REVALIDATE},
-    {"proxy-revalidate", (http_hdr_type)CC_PROXY_REVALIDATE},
-    {"only-if-cached", (http_hdr_type)CC_ONLY_IF_CACHED},
-    {"max-age", (http_hdr_type)CC_MAX_AGE},
-    {"s-maxage", (http_hdr_type)CC_S_MAXAGE},
-    {"max-stale", (http_hdr_type)CC_MAX_STALE},
-    {"stale-if-error", (http_hdr_type)CC_STALE_IF_ERROR},
-    {"min-fresh", (http_hdr_type)CC_MIN_FRESH},
-    {"Other,", (http_hdr_type)CC_OTHER}	/* ',' will protect from matches */
+#if HAVE_MAP
+#include <map>
+#endif
+
+/* a row in the table used for parsing cache control header and statistics */
+typedef struct {
+    const char *name;
+    http_hdr_cc_type id;
+    HttpHeaderFieldStat stat;
+} HttpHeaderCcFields;
+
+/* order must match that of enum http_hdr_cc_type. The constraint is verified at initialization time */
+static HttpHeaderCcFields CcAttrs[CC_ENUM_END] = {
+    {"public", CC_PUBLIC},
+    {"private", CC_PRIVATE},
+    {"no-cache", CC_NO_CACHE},
+    {"no-store", CC_NO_STORE},
+    {"no-transform", CC_NO_TRANSFORM},
+    {"must-revalidate", CC_MUST_REVALIDATE},
+    {"proxy-revalidate", CC_PROXY_REVALIDATE},
+    {"max-age", CC_MAX_AGE},
+    {"s-maxage", CC_S_MAXAGE},
+    {"max-stale", CC_MAX_STALE},
+    {"min-fresh", CC_MIN_FRESH},
+    {"only-if-cached", CC_ONLY_IF_CACHED},
+    {"stale-if-error", CC_STALE_IF_ERROR},
+    {"Other,", CC_OTHER} /* ',' will protect from matches */
 };
 
-HttpHeaderFieldInfo *CcFieldsInfo = NULL;
+/// Map an header name to its type, to expedite parsing
+typedef std::map<const StringArea,http_hdr_cc_type> CcNameToIdMap_t;
+static CcNameToIdMap_t CcNameToIdMap;
 
+/// used to walk a table of http_header_cc_type structs
 http_hdr_cc_type &operator++ (http_hdr_cc_type &aHeader)
 {
     int tmp = (int)aHeader;
     aHeader = (http_hdr_cc_type)(++tmp);
     return aHeader;
 }
 
 
-/* local prototypes */
-static int httpHdrCcParseInit(HttpHdrCc * cc, const String * str);
-
-
-/* module initialization */
-
+/// Module initialization hook
 void
 httpHdrCcInitModule(void)
 {
-    CcFieldsInfo = httpHeaderBuildFieldsInfo(CcAttrs, CC_ENUM_END);
+    /* build lookup and accounting structures */
+    for (int32_t i = 0; i < CC_ENUM_END; ++i) {
+        const HttpHeaderCcFields &f=CcAttrs[i];
+        assert(i == f.id); /* verify assumption: the id is the key into the array */
+        const StringArea k(f.name,strlen(f.name));
+        CcNameToIdMap[k]=f.id;
+    }
 }
 
+/// Module cleanup hook.
 void
 httpHdrCcCleanModule(void)
 {
-    httpHeaderDestroyFieldsInfo(CcFieldsInfo, CC_ENUM_END);
-    CcFieldsInfo = NULL;
-}
-
-/* implementation */
-
-HttpHdrCc *
-httpHdrCcCreate(void)
-{
-    HttpHdrCc *cc = (HttpHdrCc *)memAllocate(MEM_HTTP_HDR_CC);
-    cc->max_age = cc->s_maxage = cc->max_stale = cc->min_fresh = -1;
-    return cc;
+    // HdrCcNameToIdMap is self-cleaning
 }
 
-/* creates an cc object from a 0-terminating string */
-HttpHdrCc *
-httpHdrCcParseCreate(const String * str)
+void
+HttpHdrCc::clear()
 {
-    HttpHdrCc *cc = httpHdrCcCreate();
-
-    if (!httpHdrCcParseInit(cc, str)) {
-        httpHdrCcDestroy(cc);
-        cc = NULL;
-    }
-
-    return cc;
+    *this=HttpHdrCc();
 }
 
-/* parses a 0-terminating string and inits cc */
-static int
-httpHdrCcParseInit(HttpHdrCc * cc, const String * str)
+bool
+HttpHdrCc::parse(const String & str)
 {
     const char *item;
     const char *p;		/* '=' parameter */
     const char *pos = NULL;
     http_hdr_cc_type type;
     int ilen;
     int nlen;
-    assert(cc && str);
 
     /* iterate through comma separated list */
 
-    while (strListGetItem(str, ',', &item, &ilen, &pos)) {
+    while (strListGetItem(&str, ',', &item, &ilen, &pos)) {
         /* isolate directive name */
 
-        if ((p = (const char *)memchr(item, '=', ilen)) && (p - item < ilen))
-            nlen = p++ - item;
-        else
+        if ((p = (const char *)memchr(item, '=', ilen)) && (p - item < ilen)) {
+            nlen = p - item;
+            ++p;
+        } else {
             nlen = ilen;
+        }
 
         /* find type */
-        type = (http_hdr_cc_type ) httpHeaderIdByName(item, nlen,
-                CcFieldsInfo, CC_ENUM_END);
-
-        if (type < 0) {
-            debugs(65, 2, "hdr cc: unknown cache-directive: near '" << item << "' in '" << str << "'");
-            type = CC_OTHER;
-        }
+        const CcNameToIdMap_t::const_iterator i=CcNameToIdMap.find(StringArea(item,nlen));
+        if (i==CcNameToIdMap.end())
+            type=CC_OTHER;
+        else
+            type=i->second;
 
         // ignore known duplicate directives
-        if (EBIT_TEST(cc->mask, type)) {
+        if (isSet(type)) {
             if (type != CC_OTHER) {
                 debugs(65, 2, "hdr cc: ignoring duplicate cache-directive: near '" << item << "' in '" << str << "'");
-                CcFieldsInfo[type].stat.repCount++;
+                ++CcAttrs[type].stat.repCount;
                 continue;
             }
-        } else {
-            EBIT_SET(cc->mask, type);
         }
 
-        /* post-processing special cases */
+        /* special-case-parsing and attribute-setting */
         switch (type) {
 
         case CC_MAX_AGE:
-
-            if (!p || !httpHeaderParseInt(p, &cc->max_age)) {
+            if (!p || !httpHeaderParseInt(p, &max_age) || max_age < 0) {
                 debugs(65, 2, "cc: invalid max-age specs near '" << item << "'");
-                cc->max_age = -1;
-                EBIT_CLR(cc->mask, type);
+                clearMaxAge();
+            } else {
+                setMask(type,true);
             }
-
             break;
 
         case CC_S_MAXAGE:
-
-            if (!p || !httpHeaderParseInt(p, &cc->s_maxage)) {
+            if (!p || !httpHeaderParseInt(p, &s_maxage) || s_maxage < 0) {
                 debugs(65, 2, "cc: invalid s-maxage specs near '" << item << "'");
-                cc->s_maxage = -1;
-                EBIT_CLR(cc->mask, type);
+                clearSMaxAge();
+            } else {
+                setMask(type,true);
             }
-
             break;
 
         case CC_MAX_STALE:
-
-            if (!p || !httpHeaderParseInt(p, &cc->max_stale)) {
+            if (!p || !httpHeaderParseInt(p, &max_stale) || max_stale < 0) {
                 debugs(65, 2, "cc: max-stale directive is valid without value");
-                cc->max_stale = -1;
+                maxStale(MAX_STALE_ANY);
+            } else {
+                setMask(type,true);
             }
-
             break;
 
         case CC_MIN_FRESH:
-
-            if (!p || !httpHeaderParseInt(p, &cc->min_fresh)) {
+            if (!p || !httpHeaderParseInt(p, &min_fresh) || min_fresh < 0) {
                 debugs(65, 2, "cc: invalid min-fresh specs near '" << item << "'");
-                cc->min_fresh = -1;
-                EBIT_CLR(cc->mask, type);
+                clearMinFresh();
+            } else {
+                setMask(type,true);
             }
-
             break;
 
         case CC_STALE_IF_ERROR:
-            if (!p || !httpHeaderParseInt(p, &cc->stale_if_error)) {
+            if (!p || !httpHeaderParseInt(p, &stale_if_error) || stale_if_error < 0) {
                 debugs(65, 2, "cc: invalid stale-if-error specs near '" << item << "'");
-                cc->stale_if_error = -1;
-                EBIT_CLR(cc->mask, type);
+                clearStaleIfError();
+            } else {
+                setMask(type,true);
             }
             break;
 
-        case CC_OTHER:
+        case CC_PRIVATE: {
+            String temp;
+            if (!p)  {
+                // Value parameter is optional.
+                private_.clean();
+            }            else if (/* p &&*/ httpHeaderParseQuotedString(p, (ilen-nlen-1), &temp)) {
+                private_.append(temp);
+            }            else {
+                debugs(65, 2, "cc: invalid private= specs near '" << item << "'");
+            }
+            // to be safe we ignore broken parameters, but always remember the 'private' part.
+            setMask(type,true);
+        }
+        break;
 
-            if (cc->other.size())
-                cc->other.append(", ");
+        case CC_NO_CACHE: {
+            String temp;
+            if (!p) {
+                // On Requests, missing value parameter is expected syntax.
+                // On Responses, value parameter is optional.
+                setMask(type,true);
+                no_cache.clean();
+            } else if (/* p &&*/ httpHeaderParseQuotedString(p, (ilen-nlen-1), &temp)) {
+                // On Requests, a value parameter is invalid syntax.
+                // XXX: identify when parsing request header and dump err message here.
+                setMask(type,true);
+                no_cache.append(temp);
+            } else {
+                debugs(65, 2, "cc: invalid no-cache= specs near '" << item << "'");
+            }
+        }
+        break;
 
-            cc->other.append(item, ilen);
+        case CC_PUBLIC:
+            Public(true);
+            break;
+        case CC_NO_STORE:
+            noStore(true);
+            break;
+        case CC_NO_TRANSFORM:
+            noTransform(true);
+            break;
+        case CC_MUST_REVALIDATE:
+            mustRevalidate(true);
+            break;
+        case CC_PROXY_REVALIDATE:
+            proxyRevalidate(true);
+            break;
+        case CC_ONLY_IF_CACHED:
+            onlyIfCached(true);
+            break;
 
+        case CC_OTHER:
+            if (other.size())
+                other.append(", ");
+
+            other.append(item, ilen);
             break;
 
         default:
             /* note that we ignore most of '=' specs (RFCVIOLATION) */
             break;
         }
     }
 
-    return cc->mask != 0;
+    return (mask != 0);
 }
 
 void
-httpHdrCcDestroy(HttpHdrCc * cc)
-{
-    assert(cc);
-
-    if (cc->other.defined())
-        cc->other.clean();
-
-    memFree(cc, MEM_HTTP_HDR_CC);
-}
-
-HttpHdrCc *
-httpHdrCcDup(const HttpHdrCc * cc)
+HttpHdrCc::packInto(Packer * p) const
 {
-    HttpHdrCc *dup;
-    assert(cc);
-    dup = httpHdrCcCreate();
-    dup->mask = cc->mask;
-    dup->max_age = cc->max_age;
-    dup->s_maxage = cc->s_maxage;
-    dup->max_stale = cc->max_stale;
-    dup->min_fresh = cc->min_fresh;
-    return dup;
-}
+    // optimization: if the mask is empty do nothing
+    if (mask==0)
+        return;
 
-void
-httpHdrCcPackInto(const HttpHdrCc * cc, Packer * p)
-{
     http_hdr_cc_type flag;
     int pcount = 0;
-    assert(cc && p);
+    assert(p);
 
     for (flag = CC_PUBLIC; flag < CC_ENUM_END; ++flag) {
-        if (EBIT_TEST(cc->mask, flag) && flag != CC_OTHER) {
-
-            /* print option name */
-            packerPrintf(p, (pcount ? ", " SQUIDSTRINGPH : SQUIDSTRINGPH),
-                         SQUIDSTRINGPRINT(CcFieldsInfo[flag].name));
+        if (isSet(flag) && flag != CC_OTHER) {
 
-            /* handle options with values */
+            /* print option name for all options */
+            packerPrintf(p, (pcount ? ", %s": "%s") , CcAttrs[flag].name);
 
-            if (flag == CC_MAX_AGE)
-                packerPrintf(p, "=%d", (int) cc->max_age);
-
-            if (flag == CC_S_MAXAGE)
-                packerPrintf(p, "=%d", (int) cc->s_maxage);
-
-            if (flag == CC_MAX_STALE && cc->max_stale >= 0)
-                packerPrintf(p, "=%d", (int) cc->max_stale);
-
-            if (flag == CC_MIN_FRESH)
-                packerPrintf(p, "=%d", (int) cc->min_fresh);
+            /* for all options having values, "=value" after the name */
+            switch (flag) {
+            case CC_MAX_AGE:
+                packerPrintf(p, "=%d", (int) maxAge());
+                break;
+            case CC_S_MAXAGE:
+                packerPrintf(p, "=%d", (int) sMaxAge());
+                break;
+            case CC_MAX_STALE:
+                /* max-stale's value is optional.
+                  If we didn't receive it, don't send it */
+                if (maxStale()!=MAX_STALE_ANY)
+                    packerPrintf(p, "=%d", (int) maxStale());
+                break;
+            case CC_MIN_FRESH:
+                packerPrintf(p, "=%d", (int) minFresh());
+                break;
+            default:
+                /* do nothing, directive was already printed */
+                break;
+            }
 
-            pcount++;
+            ++pcount;
         }
     }
 
-    if (cc->other.size() != 0)
+    if (other.size() != 0)
         packerPrintf(p, (pcount ? ", " SQUIDSTRINGPH : SQUIDSTRINGPH),
-                     SQUIDSTRINGPRINT(cc->other));
-}
-
-/* negative max_age will clean old max_Age setting */
-void
-httpHdrCcSetMaxAge(HttpHdrCc * cc, int max_age)
-{
-    assert(cc);
-    cc->max_age = max_age;
-
-    if (max_age >= 0)
-        EBIT_SET(cc->mask, CC_MAX_AGE);
-    else
-        EBIT_CLR(cc->mask, CC_MAX_AGE);
-}
-
-/* negative s_maxage will clean old s-maxage setting */
-void
-httpHdrCcSetSMaxAge(HttpHdrCc * cc, int s_maxage)
-{
-    assert(cc);
-    cc->s_maxage = s_maxage;
-
-    if (s_maxage >= 0)
-        EBIT_SET(cc->mask, CC_S_MAXAGE);
-    else
-        EBIT_CLR(cc->mask, CC_S_MAXAGE);
+                     SQUIDSTRINGPRINT(other));
 }
 
 void
 httpHdrCcUpdateStats(const HttpHdrCc * cc, StatHist * hist)
 {
     http_hdr_cc_type c;
     assert(cc);
 
     for (c = CC_PUBLIC; c < CC_ENUM_END; ++c)
-        if (EBIT_TEST(cc->mask, c))
-            statHistCount(hist, c);
+        if (cc->isSet(c))
+            hist->count(c);
 }
 
 void
 httpHdrCcStatDumper(StoreEntry * sentry, int idx, double val, double size, int count)
 {
     extern const HttpHeaderStat *dump_stat;	/* argh! */
     const int id = (int) val;
     const int valid_id = id >= 0 && id < CC_ENUM_END;
-    const char *name = valid_id ? CcFieldsInfo[id].name.termedBuf() : "INVALID";
+    const char *name = valid_id ? CcAttrs[id].name : "INVALID";
 
     if (count || valid_id)
         storeAppendPrintf(sentry, "%2d\t %-20s\t %5d\t %6.2f\n",
                           id, name, count, xdiv(count, dump_stat->ccParsedCount));
 }
+
+#if !_USE_INLINE_
+#include "HttpHdrCc.cci"
+#endif
