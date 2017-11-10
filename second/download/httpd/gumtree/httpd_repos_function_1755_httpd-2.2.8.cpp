static apr_status_t CaseFilterInFilter(ap_filter_t *f,
                                       apr_bucket_brigade *pbbOut,
                                       ap_input_mode_t eMode,
                                       apr_read_type_e eBlock,
                                       apr_off_t nBytes)
{
    request_rec *r = f->r;
    conn_rec *c = r->connection;
    CaseFilterInContext *pCtx;
    apr_status_t ret;

    if (!(pCtx = f->ctx)) {
        f->ctx = pCtx = apr_palloc(r->pool, sizeof *pCtx);
        pCtx->pbbTmp = apr_brigade_create(r->pool, c->bucket_alloc);
    }

    if (APR_BRIGADE_EMPTY(pCtx->pbbTmp)) {
        ret = ap_get_brigade(f->next, pCtx->pbbTmp, eMode, eBlock, nBytes);

        if (eMode == AP_MODE_EATCRLF || ret != APR_SUCCESS)
            return ret;
    }

    while(!APR_BRIGADE_EMPTY(pCtx->pbbTmp)) {
        apr_bucket *pbktIn = APR_BRIGADE_FIRST(pCtx->pbbTmp);
        apr_bucket *pbktOut;
        const char *data;
        apr_size_t len;
        char *buf;
        apr_size_t n;

        /* It is tempting to do this...
         * APR_BUCKET_REMOVE(pB);
         * APR_BRIGADE_INSERT_TAIL(pbbOut,pB);
         * and change the case of the bucket data, but that would be wrong
         * for a file or socket buffer, for example...
         */

        if(APR_BUCKET_IS_EOS(pbktIn)) {
            APR_BUCKET_REMOVE(pbktIn);
            APR_BRIGADE_INSERT_TAIL(pbbOut, pbktIn);
            break;
        }

        ret=apr_bucket_read(pbktIn, &data, &len, eBlock);
        if(ret != APR_SUCCESS)
            return ret;

        buf = malloc(len);
        for(n=0 ; n < len ; ++n)
            buf[n] = apr_toupper(data[n]);

        pbktOut = apr_bucket_heap_create(buf, len, 0, c->bucket_alloc);
        APR_BRIGADE_INSERT_TAIL(pbbOut, pbktOut);
        apr_bucket_delete(pbktIn);
    }

    return APR_SUCCESS;
}