static const char *log_request_query(request_rec *r, char *a)
{
    return (r->args != NULL) ? apr_pstrcat(r->pool, "?", r->args, NULL)
                             : "";
}