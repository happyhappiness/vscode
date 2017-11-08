static const char *header_request_loadavg(request_rec *r, char *a)
{
    ap_loadavg_t t;
    ap_get_loadavg(&t);
    return apr_psprintf(r->pool, "l=%.2f/%.2f/%.2f", t.loadavg,
                        t.loadavg5, t.loadavg15);
}