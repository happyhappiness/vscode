apr_bucket * h2_bucket_headers_make(apr_bucket *b, h2_headers *r)
{
    h2_bucket_headers *br;

    br = apr_bucket_alloc(sizeof(*br), b->list);
    br->headers = r;

    b = apr_bucket_shared_make(b, br, 0, 0);
    b->type = &h2_bucket_type_headers;
    
    return b;
}