         if (node->children.concurrency)
             storeAppendPrintf(sentry, " concurrency=%d", node->children.concurrency);
 
         if (node->cache)
             storeAppendPrintf(sentry, " cache=%d", node->cache_size);
 
+        if (node->quote == external_acl::QUOTE_METHOD_SHELL)
+            storeAppendPrintf(sentry, " protocol=2.5");
+
         for (format = node->format; format; format = format->next) {
             switch (format->type) {
 
             case _external_acl_format::EXT_ACL_HEADER_REQUEST:
             case _external_acl_format::EXT_ACL_HEADER_REQUEST_ID:
                 storeAppendPrintf(sentry, " %%>{%s}", format->header);
