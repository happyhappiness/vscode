static const char *log_request_method(request_rec *r, char *a)
{
    return r->method;
}