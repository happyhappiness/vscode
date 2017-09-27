         }
 
         break;
     } while (1); /* work hard to find a match ;-) */
 
     /* no match at all, release all (wrongly) matched chars so far */
-    *release = ctx->ctx->parse_pos;
-    ctx->state = PARSE_PRE_HEAD;
+    *release = intern->parse_pos;
+    intern->state = PARSE_PRE_HEAD;
     return 0;
 }
 
 /*
  * returns the position after the directive
  */
-static apr_size_t find_directive(ssi_ctx_t *ctx, const char *data,
+static apr_size_t find_directive(include_ctx_t *ctx, const char *data,
                                  apr_size_t len, char ***store,
                                  apr_size_t **store_len)
 {
+    struct ssi_internal_ctx *intern = ctx->intern;
     const char *p = data;
     const char *ep = data + len;
     apr_size_t pos;
 
-    switch (ctx->state) {
+    switch (intern->state) {
     case PARSE_DIRECTIVE:
         while (p < ep && !apr_isspace(*p)) {
             /* we have to consider the case of missing space between directive
              * and end_seq (be somewhat lenient), e.g. <!--#printenv-->
              */
-            if (*p == *ctx->ctx->end_seq) {
-                ctx->state = PARSE_DIRECTIVE_TAIL;
-                ctx->ctx->parse_pos = 1;
+            if (*p == *intern->end_seq) {
+                intern->state = PARSE_DIRECTIVE_TAIL;
+                intern->parse_pos = 1;
                 ++p;
                 return (p - data);
             }
             ++p;
         }
 
         if (p < ep) { /* found delimiter whitespace */
-            ctx->state = PARSE_DIRECTIVE_POSTNAME;
-            *store = &ctx->directive;
-            *store_len = &ctx->ctx->directive_length;
+            intern->state = PARSE_DIRECTIVE_POSTNAME;
+            *store = &intern->directive;
+            *store_len = &intern->directive_len;
         }
 
         break;
 
     case PARSE_DIRECTIVE_TAIL:
-        pos = ctx->ctx->parse_pos;
+        pos = intern->parse_pos;
 
-        while (p < ep && pos < ctx->end_seq_len &&
-               *p == ctx->ctx->end_seq[pos]) {
+        while (p < ep && pos < intern->end_seq_len &&
+               *p == intern->end_seq[pos]) {
             ++p;
             ++pos;
         }
 
         /* full match, we're done */
-        if (pos == ctx->end_seq_len) {
-            ctx->state = PARSE_DIRECTIVE_POSTTAIL;
-            *store = &ctx->directive;
-            *store_len = &ctx->ctx->directive_length;
+        if (pos == intern->end_seq_len) {
+            intern->state = PARSE_DIRECTIVE_POSTTAIL;
+            *store = &intern->directive;
+            *store_len = &intern->directive_len;
             break;
         }
 
         /* partial match, the buffer is too small to match fully */
         if (p == ep) {
-            ctx->ctx->parse_pos = pos;
+            intern->parse_pos = pos;
             break;
         }
 
         /* no match. continue normal parsing */
-        ctx->state = PARSE_DIRECTIVE;
+        intern->state = PARSE_DIRECTIVE;
         return 0;
 
     case PARSE_DIRECTIVE_POSTTAIL:
-        ctx->state = PARSE_EXECUTE;
-        ctx->ctx->directive_length -= ctx->end_seq_len;
+        intern->state = PARSE_EXECUTE;
+        intern->directive_len -= intern->end_seq_len;
         /* continue immediately with the next state */
 
     case PARSE_DIRECTIVE_POSTNAME:
-        if (PARSE_DIRECTIVE_POSTNAME == ctx->state) {
-            ctx->state = PARSE_PRE_ARG;
+        if (PARSE_DIRECTIVE_POSTNAME == intern->state) {
+            intern->state = PARSE_PRE_ARG;
         }
         ctx->argc = 0;
-        ctx->argv = NULL;
+        intern->argv = NULL;
 
-        if (!ctx->ctx->directive_length) {
-            ctx->error = 1;
-            ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, ctx->r, "missing directive "
-                          "name in parsed document %s", ctx->r->filename);
+        if (!intern->directive_len) {
+            intern->error = 1;
+            ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, intern->r, "missing "
+                          "directive name in parsed document %s",
+                          intern->r->filename);
         }
         else {
-            char *sp = ctx->directive;
-            char *sep = ctx->directive + ctx->ctx->directive_length;
+            char *sp = intern->directive;
+            char *sep = intern->directive + intern->directive_len;
 
             /* normalize directive name */
             for (; sp < sep; ++sp) {
                 *sp = apr_tolower(*sp);
             }
         }
