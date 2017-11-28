 {
     cfg->parsePoolAccess(LegacyParser);
 }
 
 #endif
 
-#if HTTP_VIOLATIONS
-static void
-dump_http_header_access(StoreEntry * entry, const char *name, header_mangler header[])
-{
-    int i;
+#if USE_DELAY_POOLS
+#include "ClientDelayConfig.h"
+/* do nothing - free_client_delay_pool_count is the magic free function.
+ * this is why client_delay_pool_count isn't just marked TYPE: u_short
+ */
 
-    for (i = 0; i < HDR_ENUM_END; i++) {
-        if (header[i].access_list != NULL) {
-            storeAppendPrintf(entry, "%s ", name);
-            dump_acl_access(entry, httpHeaderNameById(i),
-                            header[i].access_list);
-        }
-    }
-}
+#define free_client_delay_pool_access(X)
+#define free_client_delay_pool_rates(X)
+#define dump_client_delay_pool_access(X, Y, Z)
+#define dump_client_delay_pool_rates(X, Y, Z)
 
 static void
-parse_http_header_access(header_mangler header[])
+free_client_delay_pool_count(ClientDelayConfig * cfg)
 {
-    int id, i;
-    char *t = NULL;
-
-    if ((t = strtok(NULL, w_space)) == NULL) {
-        debugs(3, 0, "" << cfg_filename << " line " << config_lineno << ": " << config_input_line);
-        debugs(3, 0, "parse_http_header_access: missing header name.");
-        return;
-    }
-
-    /* Now lookup index of header. */
-    id = httpHeaderIdByNameDef(t, strlen(t));
-
-    if (strcmp(t, "All") == 0)
-        id = HDR_ENUM_END;
-    else if (strcmp(t, "Other") == 0)
-        id = HDR_OTHER;
-    else if (id == -1) {
-        debugs(3, 0, "" << cfg_filename << " line " << config_lineno << ": " << config_input_line);
-        debugs(3, 0, "parse_http_header_access: unknown header name '" << t << "'");
-        return;
-    }
-
-    if (id != HDR_ENUM_END) {
-        parse_acl_access(&header[id].access_list);
-    } else {
-        char *next_string = t + strlen(t) - 1;
-        *next_string = 'A';
-        *(next_string + 1) = ' ';
-
-        for (i = 0; i < HDR_ENUM_END; i++) {
-            char *new_string = xstrdup(next_string);
-            strtok(new_string, w_space);
-            parse_acl_access(&header[i].access_list);
-            safe_free(new_string);
-        }
-    }
+    cfg->freePoolCount();
 }
 
 static void
-free_http_header_access(header_mangler header[])
+dump_client_delay_pool_count(StoreEntry * entry, const char *name, ClientDelayConfig &cfg)
 {
-    int i;
+    cfg.dumpPoolCount (entry, name);
+}
 
-    for (i = 0; i < HDR_ENUM_END; i++) {
-        free_acl_access(&header[i].access_list);
-    }
+static void
+parse_client_delay_pool_count(ClientDelayConfig * cfg)
+{
+    cfg->parsePoolCount();
 }
 
 static void
-dump_http_header_replace(StoreEntry * entry, const char *name, header_mangler
-                         header[])
+parse_client_delay_pool_rates(ClientDelayConfig * cfg)
 {
-    int i;
+    cfg->parsePoolRates();
+}
 
-    for (i = 0; i < HDR_ENUM_END; i++) {
-        if (NULL == header[i].replacement)
-            continue;
+static void
+parse_client_delay_pool_access(ClientDelayConfig * cfg)
+{
+    cfg->parsePoolAccess(LegacyParser);
+}
+#endif
 
-        storeAppendPrintf(entry, "%s %s %s\n", name, httpHeaderNameById(i),
-                          header[i].replacement);
-    }
+#if USE_HTTP_VIOLATIONS
+static void
+dump_http_header_access(StoreEntry * entry, const char *name, const HeaderManglers *manglers)
+{
+    if (manglers)
+        manglers->dumpAccess(entry, name);
 }
 
 static void
-parse_http_header_replace(header_mangler header[])
+parse_http_header_access(HeaderManglers **pm)
 {
-    int id, i;
     char *t = NULL;
 
     if ((t = strtok(NULL, w_space)) == NULL) {
         debugs(3, 0, "" << cfg_filename << " line " << config_lineno << ": " << config_input_line);
-        debugs(3, 0, "parse_http_header_replace: missing header name.");
+        debugs(3, 0, "parse_http_header_access: missing header name.");
         return;
     }
 
-    /* Now lookup index of header. */
-    id = httpHeaderIdByNameDef(t, strlen(t));
-
-    if (strcmp(t, "All") == 0)
-        id = HDR_ENUM_END;
-    else if (strcmp(t, "Other") == 0)
-        id = HDR_OTHER;
-    else if (id == -1) {
-        debugs(3, 0, "" << cfg_filename << " line " << config_lineno << ": " << config_input_line);
-        debugs(3, 0, "parse_http_header_replace: unknown header name " << t << ".");
+    if (!*pm)
+        *pm = new HeaderManglers;
+    HeaderManglers *manglers = *pm;
+    header_mangler *mangler = manglers->track(t);
+    assert(mangler);
+    parse_acl_access(&mangler->access_list);
+}
 
-        return;
+static void
+free_HeaderManglers(HeaderManglers **pm)
+{
+    // we delete the entire http_header_* mangler configuration at once
+    if (const HeaderManglers *manglers = *pm) {
+        delete manglers;
+        *pm = NULL;
     }
+}
 
-    if (id != HDR_ENUM_END) {
-        if (header[id].replacement != NULL)
-            safe_free(header[id].replacement);
-
-        header[id].replacement = xstrdup(t + strlen(t) + 1);
-    } else {
-        for (i = 0; i < HDR_ENUM_END; i++) {
-            if (header[i].replacement != NULL)
-                safe_free(header[i].replacement);
-
-            header[i].replacement = xstrdup(t + strlen(t) + 1);
-        }
-    }
+static void
+dump_http_header_replace(StoreEntry * entry, const char *name, const HeaderManglers *manglers)
+{
+    if (manglers)
+        manglers->dumpReplacement(entry, name);
 }
 
 static void
-free_http_header_replace(header_mangler header[])
+parse_http_header_replace(HeaderManglers **pm)
 {
-    int i;
+    char *t = NULL;
 
-    for (i = 0; i < HDR_ENUM_END; i++) {
-        if (header[i].replacement != NULL)
-            safe_free(header[i].replacement);
+    if ((t = strtok(NULL, w_space)) == NULL) {
+        debugs(3, 0, "" << cfg_filename << " line " << config_lineno << ": " << config_input_line);
+        debugs(3, 0, "parse_http_header_replace: missing header name.");
+        return;
     }
+
+    const char *value = t + strlen(t) + 1;
+
+    if (!*pm)
+        *pm = new HeaderManglers;
+    HeaderManglers *manglers = *pm;
+    manglers->setReplacement(t, value);
 }
 
 #endif
 
 static void
 dump_cachedir(StoreEntry * entry, const char *name, SquidConfig::_cacheSwap swap)
 {
     SwapDir *s;
     int i;
     assert (entry);
 
-    for (i = 0; i < swap.n_configured; i++) {
+    for (i = 0; i < swap.n_configured; ++i) {
         s = dynamic_cast<SwapDir *>(swap.swapDirs[i].getRaw());
         if (!s) continue;
         storeAppendPrintf(entry, "%s %s %s", name, s->type(), s->path);
         s->dump(*entry);
         storeAppendPrintf(entry, "\n");
     }
