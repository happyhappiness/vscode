static void calc_apr_hash(h2_push_diary *diary, apr_uint64_t *phash, h2_push *push) 
{
    apr_uint64_t val;
#if APR_UINT64_MAX > UINT_MAX
    val = ((apr_uint64_t)(val_apr_hash(push->req->scheme)) << 32);
    val ^= ((apr_uint64_t)(val_apr_hash(push->req->authority)) << 16);
    val ^= val_apr_hash(push->req->path);
#else
    val = val_apr_hash(push->req->scheme);
    val ^= val_apr_hash(push->req->authority);
    val ^= val_apr_hash(push->req->path);
#endif
    *phash = val;
}