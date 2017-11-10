static void dav_send_multistatus(request_rec *r, int status,
                                 dav_response *first,
                                 apr_array_header_t *namespaces)
{
    apr_pool_t *subpool;
    apr_bucket_brigade *bb = apr_brigade_create(r->pool,
                                                r->connection->bucket_alloc);

    dav_begin_multistatus(bb, r, status, namespaces);

    apr_pool_create(&subpool, r->pool);

    for (; first != NULL; first = first->next) {
      apr_pool_clear(subpool);
      dav_send_one_response(first, bb, r->output_filters, subpool);
    }
    apr_pool_destroy(subpool);

    dav_finish_multistatus(r, bb);
}