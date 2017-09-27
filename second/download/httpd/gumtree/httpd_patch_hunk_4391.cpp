             return apr_snprintf(buffer, maxlen,
                                 "type=%d[length=%d, flags=%d, stream=%d]",
                                 frame->hd.type, (int)frame->hd.length,
                                 frame->hd.flags, frame->hd.stream_id);
     }
 }
+
+/*******************************************************************************
+ * link header handling 
+ ******************************************************************************/
+
+typedef struct {
+    apr_pool_t *pool;
+    request_rec *r;
+    proxy_dir_conf *conf;
+    const char *s;
+    int slen;
+    int i;
+    const char *server_uri;
+    int su_len;
+    const char *real_backend_uri;
+    int rbu_len;
+    const char *p_server_uri;
+    int psu_len;
+    int link_start;
+    int link_end;
+} link_ctx;
+
+static int attr_char(char c) 
+{
+    switch (c) {
+        case '!':
+        case '#':
+        case '$':
+        case '&':
+        case '+':
+        case '-':
+        case '.':
+        case '^':
+        case '_':
+        case '`':
+        case '|':
+        case '~':
+            return 1;
+        default:
+            return apr_isalnum(c);
+    }
+}
+
+static int ptoken_char(char c) 
+{
+    switch (c) {
+        case '!':
+        case '#':
+        case '$':
+        case '&':
+        case '\'':
+        case '(':
+        case ')':
+        case '*':
+        case '+':
+        case '-':
+        case '.':
+        case '/':
+        case ':':
+        case '<':
+        case '=':
+        case '>':
+        case '?':
+        case '@':
+        case '[':
+        case ']':
+        case '^':
+        case '_':
+        case '`':
+        case '{':
+        case '|':
+        case '}':
+        case '~':
+            return 1;
+        default:
+            return apr_isalnum(c);
+    }
+}
+
+static int skip_ws(link_ctx *ctx)
+{
+    char c;
+    while (ctx->i < ctx->slen 
+           && (((c = ctx->s[ctx->i]) == ' ') || (c == '\t'))) {
+        ++ctx->i;
+    }
+    return (ctx->i < ctx->slen);
+}
+
+static int find_chr(link_ctx *ctx, char c, int *pidx)
+{
+    int j;
+    for (j = ctx->i; j < ctx->slen; ++j) {
+        if (ctx->s[j] == c) {
+            *pidx = j;
+            return 1;
+        }
+    } 
+    return 0;
+}
+
+static int read_chr(link_ctx *ctx, char c)
+{
+    if (ctx->i < ctx->slen && ctx->s[ctx->i] == c) {
+        ++ctx->i;
+        return 1;
+    }
+    return 0;
+}
+
+static int skip_qstring(link_ctx *ctx)
+{
+    if (skip_ws(ctx) && read_chr(ctx, '\"')) {
+        int end;
+        if (find_chr(ctx, '\"', &end)) {
+            ctx->i = end + 1;
+            return 1;
+        }
+    }
+    return 0;
+}
+
+static int skip_ptoken(link_ctx *ctx)
+{
+    if (skip_ws(ctx)) {
+        int i;
+        for (i = ctx->i; i < ctx->slen && ptoken_char(ctx->s[i]); ++i) {
+            /* nop */
+        }
+        if (i > ctx->i) {
+            ctx->i = i;
+            return 1;
+        }
+    }
+    return 0;
+}
+
+
+static int read_link(link_ctx *ctx)
+{
+    ctx->link_start = ctx->link_end = 0;
+    if (skip_ws(ctx) && read_chr(ctx, '<')) {
+        int end;
+        if (find_chr(ctx, '>', &end)) {
+            ctx->link_start = ctx->i;
+            ctx->link_end = end;
+            ctx->i = end + 1;
+            return 1;
+        }
+    }
+    return 0;
+}
+
+static int skip_pname(link_ctx *ctx)
+{
+    if (skip_ws(ctx)) {
+        int i;
+        for (i = ctx->i; i < ctx->slen && attr_char(ctx->s[i]); ++i) {
+            /* nop */
+        }
+        if (i > ctx->i) {
+            ctx->i = i;
+            return 1;
+        }
+    }
+    return 0;
+}
+
+static int skip_pvalue(link_ctx *ctx)
+{
+    if (skip_ws(ctx) && read_chr(ctx, '=')) {
+        if (skip_qstring(ctx) || skip_ptoken(ctx)) {
+            return 1;
+        }
+    }
+    return 0;
+}
+
+static int skip_param(link_ctx *ctx)
+{
+    if (skip_ws(ctx) && read_chr(ctx, ';')) {
+        if (skip_pname(ctx)) {
+            skip_pvalue(ctx); /* value is optional */
+            return 1;
+        }
+    }
+    return 0;
+}
+
+static int read_sep(link_ctx *ctx)
+{
+    if (skip_ws(ctx) && read_chr(ctx, ',')) {
+        return 1;
+    }
+    return 0;
+}
+
+static size_t subst_str(link_ctx *ctx, int start, int end, const char *ns)
+{
+    int olen, nlen, plen;
+    int delta;
+    char *p;
+    
+    olen = end - start;
+    nlen = (int)strlen(ns);
+    delta = nlen - olen;
+    plen = ctx->slen + delta + 1;
+    p = apr_pcalloc(ctx->pool, plen);
+    strncpy(p, ctx->s, start);
+    strncpy(p + start, ns, nlen);
+    strcpy(p + start + nlen, ctx->s + end);
+    ctx->s = p;
+    ctx->slen = (int)strlen(p);
+    if (ctx->i >= end) {
+        ctx->i += delta;
+    }
+    return nlen; 
+}
+
+static void map_link(link_ctx *ctx) 
+{
+    if (ctx->link_start < ctx->link_end) {
+        char buffer[HUGE_STRING_LEN];
+        int need_len, link_len, buffer_len, prepend_p_server; 
+        const char *mapped;
+        
+        buffer[0] = '\0';
+        buffer_len = 0;
+        link_len = ctx->link_end - ctx->link_start;
+        need_len = link_len + 1;
+        prepend_p_server = (ctx->s[ctx->link_start] == '/'); 
+        if (prepend_p_server) {
+            /* common to use relative uris in link header, for mappings
+             * to work need to prefix the backend server uri */
+            need_len += ctx->psu_len;
+            strncpy(buffer, ctx->p_server_uri, sizeof(buffer));
+            buffer_len = ctx->psu_len;
+        }
+        if (need_len > sizeof(buffer)) {
+            ap_log_rerror(APLOG_MARK, APLOG_WARNING, 0, ctx->r, APLOGNO(03482) 
+                          "link_reverse_map uri too long, skipped: %s", ctx->s);
+            return;
+        }
+        strncpy(buffer + buffer_len, ctx->s + ctx->link_start, link_len);
+        buffer_len += link_len;
+        buffer[buffer_len] = '\0';
+        if (!prepend_p_server
+            && strcmp(ctx->real_backend_uri, ctx->p_server_uri)
+            && !strncmp(buffer, ctx->real_backend_uri, ctx->rbu_len)) {
+            /* the server uri and our local proxy uri we use differ, for mapping
+             * to work, we need to use the proxy uri */
+            int path_start = ctx->link_start + ctx->rbu_len;
+            link_len -= ctx->rbu_len;
+            strcpy(buffer, ctx->p_server_uri);
+            strncpy(buffer + ctx->psu_len, ctx->s + path_start, link_len);
+            buffer_len = ctx->psu_len + link_len;
+            buffer[buffer_len] = '\0';            
+        }
+        mapped = ap_proxy_location_reverse_map(ctx->r, ctx->conf, buffer);
+        ap_log_rerror(APLOG_MARK, APLOG_TRACE2, 0, ctx->r, 
+                      "reverse_map[%s] %s --> %s", ctx->p_server_uri, buffer, mapped);
+        if (mapped != buffer) {
+            if (prepend_p_server) {
+                if (ctx->server_uri == NULL) {
+                    ctx->server_uri = ap_construct_url(ctx->pool, "", ctx->r);
+                    ctx->su_len = (int)strlen(ctx->server_uri);
+                }
+                if (!strncmp(mapped, ctx->server_uri, ctx->su_len)) {
+                    mapped += ctx->su_len;
+                }
+            }
+            subst_str(ctx, ctx->link_start, ctx->link_end, mapped);
+        }
+    }
+}
+
+/* RFC 5988 <https://tools.ietf.org/html/rfc5988#section-6.2.1>
+  Link           = "Link" ":" #link-value
+  link-value     = "<" URI-Reference ">" *( ";" link-param )
+  link-param     = ( ( "rel" "=" relation-types )
+                 | ( "anchor" "=" <"> URI-Reference <"> )
+                 | ( "rev" "=" relation-types )
+                 | ( "hreflang" "=" Language-Tag )
+                 | ( "media" "=" ( MediaDesc | ( <"> MediaDesc <"> ) ) )
+                 | ( "title" "=" quoted-string )
+                 | ( "title*" "=" ext-value )
+                 | ( "type" "=" ( media-type | quoted-mt ) )
+                 | ( link-extension ) )
+  link-extension = ( parmname [ "=" ( ptoken | quoted-string ) ] )
+                 | ( ext-name-star "=" ext-value )
+  ext-name-star  = parmname "*" ; reserved for RFC2231-profiled
+                                ; extensions.  Whitespace NOT
+                                ; allowed in between.
+  ptoken         = 1*ptokenchar
+  ptokenchar     = "!" | "#" | "$" | "%" | "&" | "'" | "("
+                 | ")" | "*" | "+" | "-" | "." | "/" | DIGIT
+                 | ":" | "<" | "=" | ">" | "?" | "@" | ALPHA
+                 | "[" | "]" | "^" | "_" | "`" | "{" | "|"
+                 | "}" | "~"
+  media-type     = type-name "/" subtype-name
+  quoted-mt      = <"> media-type <">
+  relation-types = relation-type
+                 | <"> relation-type *( 1*SP relation-type ) <">
+  relation-type  = reg-rel-type | ext-rel-type
+  reg-rel-type   = LOALPHA *( LOALPHA | DIGIT | "." | "-" )
+  ext-rel-type   = URI
+  
+  and from <https://tools.ietf.org/html/rfc5987>
+  parmname      = 1*attr-char
+  attr-char     = ALPHA / DIGIT
+                   / "!" / "#" / "$" / "&" / "+" / "-" / "."
+                   / "^" / "_" / "`" / "|" / "~"
+ */
+
+const char *h2_proxy_link_reverse_map(request_rec *r,
+                                      proxy_dir_conf *conf, 
+                                      const char *real_backend_uri,
+                                      const char *proxy_server_uri,
+                                      const char *s)
+{
+    link_ctx ctx;
+    
+    if (r->proxyreq != PROXYREQ_REVERSE) {
+        return s;
+    }
+    memset(&ctx, 0, sizeof(ctx));
+    ctx.r = r;
+    ctx.pool = r->pool;
+    ctx.conf = conf;
+    ctx.real_backend_uri = real_backend_uri;
+    ctx.rbu_len = (int)strlen(ctx.real_backend_uri);
+    ctx.p_server_uri = proxy_server_uri;
+    ctx.psu_len = (int)strlen(ctx.p_server_uri);
+    ctx.s = s;
+    ctx.slen = (int)strlen(s);
+    while (read_link(&ctx)) {
+        while (skip_param(&ctx)) {
+            /* nop */
+        }
+        map_link(&ctx);
+        if (!read_sep(&ctx)) {
+            break;
+        }
+    }
+    ap_log_rerror(APLOG_MARK, APLOG_TRACE2, 0, r, 
+                  "link_reverse_map %s --> %s", s, ctx.s);
+    return ctx.s;
+}
