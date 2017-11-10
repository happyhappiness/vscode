static const char *header_request_busy(request_rec *r, char *a)
{
    ap_sload_t t;
    ap_get_sload(&t);
    return apr_psprintf(r->pool, "b=%d", t.busy);
}