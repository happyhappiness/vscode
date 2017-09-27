     return (p - data);
 }
 
 /*
  * find out whether the next token is (a possible) end_seq or an argument
  */
-static apr_size_t find_arg_or_tail(ssi_ctx_t *ctx, const char *data,
+static apr_size_t find_arg_or_tail(include_ctx_t *ctx, const char *data,
                                    apr_size_t len)
 {
+    struct ssi_internal_ctx *intern = ctx->intern;
     const char *p = data;
     const char *ep = data + len;
 
     /* skip leading WS */
     while (p < ep && apr_isspace(*p)) {
         ++p;
     }
 
     /* buffer doesn't consist of whitespaces only */
     if (p < ep) {
-        ctx->state = (*p == *ctx->ctx->end_seq) ? PARSE_TAIL : PARSE_ARG;
+        intern->state = (*p == *intern->end_seq) ? PARSE_TAIL : PARSE_ARG;
     }
 
     return (p - data);
 }
 
 /*
  * test the stream for end_seq. If it doesn't match at all, it must be an
  * argument
  */
-static apr_size_t find_tail(ssi_ctx_t *ctx, const char *data,
+static apr_size_t find_tail(include_ctx_t *ctx, const char *data,
                             apr_size_t len)
 {
+    struct ssi_internal_ctx *intern = ctx->intern;
     const char *p = data;
     const char *ep = data + len;
-    apr_size_t pos = ctx->ctx->parse_pos;
+    apr_size_t pos = intern->parse_pos;
 
-    if (PARSE_TAIL == ctx->state) {
-        ctx->state = PARSE_TAIL_SEQ;
-        pos = ctx->ctx->parse_pos = 0;
+    if (PARSE_TAIL == intern->state) {
+        intern->state = PARSE_TAIL_SEQ;
+        pos = intern->parse_pos = 0;
     }
 
-    while (p < ep && pos < ctx->end_seq_len && *p == ctx->ctx->end_seq[pos]) {
+    while (p < ep && pos < intern->end_seq_len && *p == intern->end_seq[pos]) {
         ++p;
         ++pos;
     }
 
     /* bingo, full match */
-    if (pos == ctx->end_seq_len) {
-        ctx->state = PARSE_EXECUTE;
+    if (pos == intern->end_seq_len) {
+        intern->state = PARSE_EXECUTE;
         return (p - data);
     }
 
     /* partial match, the buffer is too small to match fully */
     if (p == ep) {
-        ctx->ctx->parse_pos = pos;
+        intern->parse_pos = pos;
         return (p - data);
     }
 
-    /* no match. It must be an argument string then */
-    ctx->state = PARSE_ARG;
+    /* no match. It must be an argument string then
+     * The caller should cleanup and rewind to the reparse point
+     */
+    intern->state = PARSE_ARG;
     return 0;
 }
 
 /*
  * extract name=value from the buffer
  * A pcre-pattern could look (similar to):
  * name\s*(?:=\s*(["'`]?)value\1(?>\s*))?
  */
-static apr_size_t find_argument(ssi_ctx_t *ctx, const char *data,
+static apr_size_t find_argument(include_ctx_t *ctx, const char *data,
                                 apr_size_t len, char ***store,
                                 apr_size_t **store_len)
 {
+    struct ssi_internal_ctx *intern = ctx->intern;
     const char *p = data;
     const char *ep = data + len;
 
-    switch (ctx->state) {
+    switch (intern->state) {
     case PARSE_ARG:
         /*
          * create argument structure and append it to the current list
          */
-        ctx->current_arg = apr_palloc(ctx->dpool,
-                                      sizeof(*ctx->current_arg));
-        ctx->current_arg->next = NULL;
+        intern->current_arg = apr_palloc(ctx->dpool,
+                                         sizeof(*intern->current_arg));
+        intern->current_arg->next = NULL;
 
         ++(ctx->argc);
-        if (!ctx->argv) {
-            ctx->argv = ctx->current_arg;
+        if (!intern->argv) {
+            intern->argv = intern->current_arg;
         }
         else {
-            ssi_arg_item_t *newarg = ctx->argv;
+            arg_item_t *newarg = intern->argv;
 
             while (newarg->next) {
                 newarg = newarg->next;
             }
-            newarg->next = ctx->current_arg;
+            newarg->next = intern->current_arg;
         }
 
         /* check whether it's a valid one. If it begins with a quote, we
          * can safely assume, someone forgot the name of the argument
          */
         switch (*p) {
         case '"': case '\'': case '`':
             *store = NULL;
 
-            ctx->state = PARSE_ARG_VAL;
-            ctx->quote = *p++;
-            ctx->current_arg->name = NULL;
-            ctx->current_arg->name_len = 0;
-            ctx->error = 1;
-
-            ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, ctx->r, "missing argument "
-                          "name for value to tag %s in %s",
-                          apr_pstrmemdup(ctx->r->pool, ctx->directive,
-                                         ctx->ctx->directive_length),
-                                         ctx->r->filename);
+            intern->state = PARSE_ARG_VAL;
+            intern->quote = *p++;
+            intern->current_arg->name = NULL;
+            intern->current_arg->name_len = 0;
+            intern->error = 1;
+
+            ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, intern->r, "missing "
+                          "argument name for value to tag %s in %s",
+                          apr_pstrmemdup(intern->r->pool, intern->directive,
+                                         intern->directive_len),
+                                         intern->r->filename);
 
             return (p - data);
 
         default:
-            ctx->state = PARSE_ARG_NAME;
+            intern->state = PARSE_ARG_NAME;
         }
         /* continue immediately with next state */
 
     case PARSE_ARG_NAME:
         while (p < ep && !apr_isspace(*p) && *p != '=') {
             ++p;
         }
 
         if (p < ep) {
-            ctx->state = PARSE_ARG_POSTNAME;
-            *store = &ctx->current_arg->name;
-            *store_len = &ctx->current_arg->name_len;
+            intern->state = PARSE_ARG_POSTNAME;
+            *store = &intern->current_arg->name;
+            *store_len = &intern->current_arg->name_len;
             return (p - data);
         }
         break;
 
     case PARSE_ARG_POSTNAME:
-        ctx->current_arg->name = apr_pstrmemdup(ctx->dpool,
-                                                ctx->current_arg->name,
-                                                ctx->current_arg->name_len);
-        if (!ctx->current_arg->name_len) {
-            ctx->error = 1;
-            ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, ctx->r, "missing argument "
-                          "name for value to tag %s in %s",
-                          apr_pstrmemdup(ctx->r->pool, ctx->directive,
-                                         ctx->ctx->directive_length),
-                                         ctx->r->filename);
+        intern->current_arg->name = apr_pstrmemdup(ctx->dpool,
+                                                 intern->current_arg->name,
+                                                 intern->current_arg->name_len);
+        if (!intern->current_arg->name_len) {
+            intern->error = 1;
+            ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, intern->r, "missing "
+                          "argument name for value to tag %s in %s",
+                          apr_pstrmemdup(intern->r->pool, intern->directive,
+                                         intern->directive_len),
+                                         intern->r->filename);
         }
         else {
-            char *sp = ctx->current_arg->name;
+            char *sp = intern->current_arg->name;
 
             /* normalize the name */
             while (*sp) {
                 *sp = apr_tolower(*sp);
                 ++sp;
             }
         }
 
-        ctx->state = PARSE_ARG_EQ;
+        intern->state = PARSE_ARG_EQ;
         /* continue with next state immediately */
 
     case PARSE_ARG_EQ:
         *store = NULL;
 
         while (p < ep && apr_isspace(*p)) {
             ++p;
         }
 
         if (p < ep) {
             if (*p == '=') {
-                ctx->state = PARSE_ARG_PREVAL;
+                intern->state = PARSE_ARG_PREVAL;
                 ++p;
             }
             else { /* no value */
-                ctx->current_arg->value = NULL;
-                ctx->state = PARSE_PRE_ARG;
+                intern->current_arg->value = NULL;
+                intern->state = PARSE_PRE_ARG;
             }
 
             return (p - data);
         }
         break;
 
