static BIO_bucket_t *BIO_bucket_new(SSLFilterRec *frec, conn_rec *c)
{
    BIO_bucket_t *b = apr_palloc(c->pool, sizeof(*b));

    b->frec = frec;
    b->c = c;
    b->bb = apr_brigade_create(c->pool, c->bucket_alloc);
    b->blen = 0;
    b->length = 0;

    return b;
}