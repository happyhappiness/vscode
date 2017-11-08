static void brigade_dump(request_rec *r, apr_bucket_brigade *bb)
{
    apr_bucket *e;
    int i = 0;

    for (e = APR_BRIGADE_FIRST(bb);
         e != APR_BRIGADE_SENTINEL(bb); e = APR_BUCKET_NEXT(e), i++) {
        ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r, APLOGNO(03193)
                      "brigade: [%d] %s", i, e->type->name);

    }
}