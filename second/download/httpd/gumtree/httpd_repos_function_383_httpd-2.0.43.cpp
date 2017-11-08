static const char *log_request_protocol(request_rec *r, char *a)
{
    return r->protocol;
}