h2_push_diary *h2_push_diary_create(apr_pool_t *p, apr_size_t N)
{
    return diary_create(p, H2_PUSH_DIGEST_SHA256, N);
}