static apr_bucket * h2_beam_bucket_make(apr_bucket *b, 
                                        h2_bucket_beam *beam,
                                        apr_bucket *bsender, apr_size_t n)
{
    h2_beam_proxy *d;

    d = apr_bucket_alloc(sizeof(*d), b->list);
    H2_BPROXY_LIST_INSERT_TAIL(&beam->proxies, d);
    d->beam = beam;
    d->bsender = bsender;
    d->n = n;
    
    b = apr_bucket_shared_make(b, d, 0, bsender? bsender->length : 0);
    b->type = &h2_bucket_type_beam;

    return b;
}