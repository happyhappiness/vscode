static void map_link(link_ctx *ctx) 
{
    if (ctx->link_start < ctx->link_end) {
        char buffer[HUGE_STRING_LEN];
        int need_len, link_len, buffer_len, prepend_p_server; 
        const char *mapped;
        
        buffer[0] = '\0';
        buffer_len = 0;
        link_len = ctx->link_end - ctx->link_start;
        need_len = link_len + 1;
        prepend_p_server = (ctx->s[ctx->link_start] == '/'); 
        if (prepend_p_server) {
            /* common to use relative uris in link header, for mappings
             * to work need to prefix the backend server uri */
            need_len += ctx->psu_len;
            strncpy(buffer, ctx->p_server_uri, sizeof(buffer));
            buffer_len = ctx->psu_len;
        }
        if (need_len > sizeof(buffer)) {
            ap_log_rerror(APLOG_MARK, APLOG_WARNING, 0, ctx->r, APLOGNO(03482) 
                          "link_reverse_map uri too long, skipped: %s", ctx->s);
            return;
        }
        strncpy(buffer + buffer_len, ctx->s + ctx->link_start, link_len);
        buffer_len += link_len;
        buffer[buffer_len] = '\0';
        if (!prepend_p_server
            && strcmp(ctx->real_backend_uri, ctx->p_server_uri)
            && !strncmp(buffer, ctx->real_backend_uri, ctx->rbu_len)) {
            /* the server uri and our local proxy uri we use differ, for mapping
             * to work, we need to use the proxy uri */
            int path_start = ctx->link_start + ctx->rbu_len;
            link_len -= ctx->rbu_len;
            strcpy(buffer, ctx->p_server_uri);
            strncpy(buffer + ctx->psu_len, ctx->s + path_start, link_len);
            buffer_len = ctx->psu_len + link_len;
            buffer[buffer_len] = '\0';            
        }
        mapped = ap_proxy_location_reverse_map(ctx->r, ctx->conf, buffer);
        ap_log_rerror(APLOG_MARK, APLOG_TRACE2, 0, ctx->r, 
                      "reverse_map[%s] %s --> %s", ctx->p_server_uri, buffer, mapped);
        if (mapped != buffer) {
            if (prepend_p_server) {
                if (ctx->server_uri == NULL) {
                    ctx->server_uri = ap_construct_url(ctx->pool, "", ctx->r);
                    ctx->su_len = (int)strlen(ctx->server_uri);
                }
                if (!strncmp(mapped, ctx->server_uri, ctx->su_len)) {
                    mapped += ctx->su_len;
                }
            }
            subst_str(ctx, ctx->link_start, ctx->link_end, mapped);
        }
    }
}