    if (!h2_util_ignore_header(key)) {
        (*((size_t*)ctx))++;
    }
    return 1;
}

static const char *inv_field_name_chr(const char *token)
{
    const char *p = ap_scan_http_token(token);
    if (p == token && *p == ':') {
        p = ap_scan_http_token(++p);
    }
    return (p && *p)? p : NULL;
}

static const char *inv_field_value_chr(const char *token)
{
    const char *p = ap_scan_http_field_content(token);
    return (p && *p)? p : NULL;
}

typedef struct ngh_ctx {
    apr_pool_t *p;
    int unsafe;
    h2_ngheader *ngh;
    apr_status_t status;
} ngh_ctx;

static int add_header(ngh_ctx *ctx, const char *key, const char *value)
{
    nghttp2_nv *nv = &(ctx->ngh)->nv[(ctx->ngh)->nvlen++];
    const char *p;

    if (!ctx->unsafe) {
        if ((p = inv_field_name_chr(key))) {
            ap_log_perror(APLOG_MARK, APLOG_TRACE1, APR_EINVAL, ctx->p,
                          "h2_request: head field '%s: %s' has invalid char %s", 
                          key, value, p);
            ctx->status = APR_EINVAL;
            return 0;
        }
        if ((p = inv_field_value_chr(value))) {
            ap_log_perror(APLOG_MARK, APLOG_TRACE1, APR_EINVAL, ctx->p,
                          "h2_request: head field '%s: %s' has invalid char %s", 
                          key, value, p);
            ctx->status = APR_EINVAL;
            return 0;
        }
    }
    nv->name = (uint8_t*)key;
    nv->namelen = strlen(key);
    nv->value = (uint8_t*)value;
    nv->valuelen = strlen(value);
    
    return 1;
}

static int add_table_header(void *ctx, const char *key, const char *value)
{
    if (!h2_util_ignore_header(key)) {
        add_header(ctx, key, value);
    }
    return 1;
}

static apr_status_t ngheader_create(h2_ngheader **ph, apr_pool_t *p, 
                                    int unsafe, size_t key_count, 
                                    const char *keys[], const char *values[],
                                    apr_table_t *headers)
{
    ngh_ctx ctx;
    size_t n, i;
    
    ctx.p = p;
    ctx.unsafe = unsafe;
    
    n = key_count;
    apr_table_do(count_header, &n, headers, NULL);
    
    *ph = ctx.ngh = apr_pcalloc(p, sizeof(h2_ngheader));
    if (!ctx.ngh) {
        return APR_ENOMEM;
    }
    
    ctx.ngh->nv =  apr_pcalloc(p, n * sizeof(nghttp2_nv));
    if (!ctx.ngh->nv) {
        return APR_ENOMEM;
    }
    
    ctx.status = APR_SUCCESS;
    for (i = 0; i < key_count; ++i) {
        if (!add_header(&ctx, keys[i], values[i])) {
            return ctx.status;
        }
    }
    
    apr_table_do(add_table_header, &ctx, headers, NULL);

    return ctx.status;
}

static int is_unsafe(h2_headers *h)
{
    const char *v = apr_table_get(h->notes, H2_HDR_CONFORMANCE);
    return (v && !strcmp(v, H2_HDR_CONFORMANCE_UNSAFE));
}

apr_status_t h2_res_create_ngtrailer(h2_ngheader **ph, apr_pool_t *p, 
                                    h2_headers *headers)
{
    return ngheader_create(ph, p, is_unsafe(headers), 
                           0, NULL, NULL, headers->headers);
}
                                     
apr_status_t h2_res_create_ngheader(h2_ngheader **ph, apr_pool_t *p,
                                    h2_headers *headers) 
{
    const char *keys[] = {
        ":status"
    };
    const char *values[] = {
        apr_psprintf(p, "%d", headers->status)
    };
    return ngheader_create(ph, p, is_unsafe(headers),  
                           H2_ALEN(keys), keys, values, headers->headers);
}

apr_status_t h2_req_create_ngheader(h2_ngheader **ph, apr_pool_t *p, 
                                    const struct h2_request *req)
{
    
    const char *keys[] = {
        ":scheme", 
        ":authority", 
        ":path", 
        ":method", 
    };
    const char *values[] = {
        req->scheme,
        req->authority, 
        req->path, 
        req->method, 
    };
    
    ap_assert(req->scheme);
    ap_assert(req->authority);
    ap_assert(req->path);
    ap_assert(req->method);

    return ngheader_create(ph, p, 0, H2_ALEN(keys), keys, values, req->headers);
}

/*******************************************************************************
 * header HTTP/1 <-> HTTP/2 conversions
 ******************************************************************************/
 
