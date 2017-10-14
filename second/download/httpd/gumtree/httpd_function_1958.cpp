static int proxy_connect_canon(request_rec *r, char *url)
{

    if (r->method_number != M_CONNECT) {
    return DECLINED;
    }
    ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, r->server,
         "proxy: CONNECT: canonicalising URL %s", url);

    return OK;
}