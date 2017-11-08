static const char *header_request_idle(request_rec *r, char *a)
{
    ap_sload_t t;
    ap_get_sload(&t);
    return apr_psprintf(r->pool, "i=%d", t.idle);
}