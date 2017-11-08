static const char *log_request_file(request_rec *r, char *a)
{
    return r->filename;
}