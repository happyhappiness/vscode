static const char *log_remote_logname(request_rec *r, char *a)
{
    return ap_get_remote_logname(r);
}