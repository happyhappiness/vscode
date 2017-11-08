static apr_status_t dav_finish_multistatus(request_rec *r,
                                           apr_bucket_brigade *bb)
{
    apr_bucket *b;
    
    ap_fputs(r->output_filters, bb, "</D:multistatus>" DEBUG_CR);
    
    /* indicate the end of the response body */
    b = apr_bucket_eos_create(r->connection->bucket_alloc);
    APR_BRIGADE_INSERT_TAIL(bb, b);

    /* deliver whatever might be remaining in the brigade */
    return ap_pass_brigade(r->output_filters, bb);
}