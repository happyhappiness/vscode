static const char *log_child_pid(request_rec *r, char *a)
{
    return apr_psprintf(r->pool, "%ld", (long) getpid());
}