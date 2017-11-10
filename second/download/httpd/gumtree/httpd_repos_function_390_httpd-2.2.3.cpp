static const char *log_status(request_rec *r, char *a)
{
    return pfmt(r->pool, r->status);
}