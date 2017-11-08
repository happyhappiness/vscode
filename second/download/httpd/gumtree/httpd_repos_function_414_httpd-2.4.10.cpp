static const char *log_request_query(request_rec *r, char *a)
{
    return (r->args) ? apr_pstrcat(r->pool, "?",
                                   ap_escape_logitem(r->pool, r->args), NULL)
                     : "";
}