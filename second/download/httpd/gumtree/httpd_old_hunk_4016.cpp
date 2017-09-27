    return 1;
}

apr_array_header_t *h2_push_collect(apr_pool_t *p, const h2_request *req, 
                                    const h2_response *res)
{
    /* Collect push candidates from the request/response pair.
     * 
     * One source for pushes are "rel=preload" link headers
     * in the response.
     * 
     * TODO: This may be extended in the future by hooks or callbacks
     * where other modules can provide push information directly.
     */
    if (res->headers) {
        link_ctx ctx;
        
        memset(&ctx, 0, sizeof(ctx));
        ctx.req = req;
        ctx.pool = p;
    
        apr_table_do(head_iter, &ctx, res->headers, NULL);
        return ctx.pushes;
    }
    return NULL;
}
