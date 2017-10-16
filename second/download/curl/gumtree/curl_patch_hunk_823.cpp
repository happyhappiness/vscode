 /* use our own printf() functions */
 #include "curlx.h"
 
 #include "tool_cfgable.h"
 #include "tool_convert.h"
 #include "tool_operhlp.h"
-#include "tool_version.h"
 #include "tool_metalink.h"
 
 #include "memdebug.h" /* keep this as LAST include */
 
-/*
- * my_useragent: returns allocated string with default user agent
- */
-char *my_useragent(void)
-{
-  return strdup( CURL_NAME "/" CURL_VERSION );
-}
-
-/*
- * Print list of OpenSSL supported engines
- */
-void list_engines(const struct curl_slist *engines)
-{
-  puts("Build-time engines:");
-  if(!engines) {
-    puts("  <none>");
-    return;
-  }
-  for(; engines; engines = engines->next)
-    printf("  %s\n", engines->data);
-}
-
-void clean_getout(struct Configurable *config)
+void clean_getout(struct OperationConfig *config)
 {
   struct getout *next;
   struct getout *node = config->url_list;
 
   while(node) {
     next = node->next;
